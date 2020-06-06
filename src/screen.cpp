#include <iostream>
#include "screen.h"

void screen::CaptureScreen(const std::string &path, const std::string &name) {
  using namespace Gdiplus;
  GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;
  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
  {
	HDC scr_dc, mem_dc;
	HBITMAP mem_bit;
	scr_dc = GetDC(nullptr);
	int Height = GetSystemMetrics(SM_CYSCREEN);
	int Width = GetSystemMetrics(SM_CXSCREEN);
	mem_dc = CreateCompatibleDC(scr_dc);
	mem_bit = CreateCompatibleBitmap(scr_dc, Width, Height);
	auto hOldBitmap = (HBITMAP)SelectObject(mem_dc, mem_bit);
	BitBlt(mem_dc, 0, 0, Width, Height, scr_dc, 0, 0, SRCCOPY);

	Gdiplus::Bitmap bitmap(mem_bit, nullptr);
	CLSID cls_id;
	screen::GetEncoderClsId(L"image/jpeg", &cls_id);
	std::wstring w_path = std::wstring(path.begin(), path.end());
	std::wstring w_name = std::wstring(name.begin(), name.end());
	std::wstring x = w_path + w_name;
	const WCHAR *full_name = x.c_str();
	bitmap.Save(full_name, &cls_id);

	SelectObject(mem_dc, hOldBitmap);
	DeleteObject(mem_dc);
	DeleteObject(mem_bit);
	ReleaseDC(nullptr, scr_dc);
  }
  GdiplusShutdown(gdiplusToken);
}

int screen::GetEncoderClsId(const WCHAR *format, CLSID *cls_id) {
  using namespace Gdiplus;
  UINT enc_size = 0;
  UINT byte_size = 0;

  ImageCodecInfo *pImageCodecInfo = nullptr;

  GetImageEncodersSize(&enc_size, &byte_size);
  if (byte_size==0) {
	return -1;
  }

  pImageCodecInfo = (ImageCodecInfo *)(malloc(byte_size));
  if (pImageCodecInfo==nullptr) {
	return -1;
  }
  GetImageEncoders(enc_size, byte_size, pImageCodecInfo);

  for (UINT j = 0; j < enc_size; ++j) {
	if (wcscmp(pImageCodecInfo[j].MimeType, format)==0) {
	  *cls_id = pImageCodecInfo[j].Clsid;
	  free(pImageCodecInfo);
	  return j;
	}
  }
  free(pImageCodecInfo);
  return 0;
}