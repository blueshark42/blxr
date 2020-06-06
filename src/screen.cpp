#include <iostream>
#include "screen.h"

int screen::GetEncoderClsId(const WCHAR *format, CLSID *cls_id) {
  using namespace Gdiplus;
  UINT enc_size = 0;
  UINT byte_size = 0;

  ImageCodecInfo *kImageCodecInfo = nullptr;

  GetImageEncodersSize(&enc_size, &byte_size);
  if (byte_size==0) {
	return -1;
  }

  kImageCodecInfo = (ImageCodecInfo *)(malloc(byte_size));
  if (kImageCodecInfo==nullptr) {
	return -1;
  }
  GetImageEncoders(enc_size, byte_size, kImageCodecInfo);

  for (UINT j = 0; j < enc_size; ++j) {
	if (wcscmp(kImageCodecInfo[j].MimeType, format)==0) {
	  *cls_id = kImageCodecInfo[j].Clsid;
	  free(kImageCodecInfo);
	  return j;
	}
  }
  free(kImageCodecInfo);
  return 0;
}

void screen::CaptureScreen(const std::string &path, const std::string &name) {
  using namespace Gdiplus;
  GdiplusStartupInput gdiplus_startup_input;
  ULONG_PTR kGdiplusToken;
  GdiplusStartup(&kGdiplusToken, &gdiplus_startup_input, nullptr);
  {
	HDC scr_dc, mem_dc;
	HBITMAP mem_bit;
	scr_dc = GetDC(nullptr);
	int kHeight = GetSystemMetrics(SM_CYSCREEN);
	int kWidth = GetSystemMetrics(SM_CXSCREEN);
	mem_dc = CreateCompatibleDC(scr_dc);
	mem_bit = CreateCompatibleBitmap(scr_dc, kWidth, kHeight);
	auto kOldBitmap = (HBITMAP)SelectObject(mem_dc, mem_bit);
	BitBlt(mem_dc, 0, 0, kWidth, kHeight, scr_dc, 0, 0, SRCCOPY);

	Gdiplus::Bitmap bitmap(mem_bit, nullptr);
	CLSID cls_id;

	screen::GetEncoderClsId(L"image/jpeg", &cls_id);
	std::wstring w_full = std::wstring(path.begin(), path.end())
		+ std::wstring(name.begin(), name.end());
	const WCHAR *full_name = w_full.c_str();

	bitmap.Save(full_name, &cls_id);

	SelectObject(mem_dc, kOldBitmap);
	DeleteObject(mem_dc);
	DeleteObject(mem_bit);
	ReleaseDC(nullptr, scr_dc);
  }
  GdiplusShutdown(kGdiplusToken);
}
