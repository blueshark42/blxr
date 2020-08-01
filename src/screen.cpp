#include <iostream>

#include "screen.h"
#include "debug.h"

int Screen::GetEncoderClsId(const WCHAR *format, CLSID *clsId) {
  using namespace Gdiplus;
  UINT encSize = 0;
  UINT byteSize = 0;

  ImageCodecInfo *imageCodecInfo;

  GetImageEncodersSize(&encSize, &byteSize);
  if (byteSize == 0) {
	return -1;
  }

  imageCodecInfo = (ImageCodecInfo *)(malloc(byteSize));
  if (imageCodecInfo == nullptr) {
	return -1;
  }
  GetImageEncoders(encSize, byteSize, imageCodecInfo);

  for (UINT i = 0; i < encSize; ++i) {
	if (wcscmp(imageCodecInfo[i].MimeType, format) == 0) {
	  *clsId = imageCodecInfo[i].Clsid;
	  free(imageCodecInfo);
	  return i;
	}
  }
  free(imageCodecInfo);
  return 0;
}

void Screen::CaptureScreen(const std::string &path,
						   const std::string &name,
						   bool loopForever,
						   int delay,
						   int loopAmount) {
  using namespace Gdiplus;
  GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;
  int loopIdx = 0;

  while (loopForever || loopIdx++ < loopAmount) {
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	{
	  HDC srcDc, memDc;
	  HBITMAP memBit;
	  srcDc = GetDC(nullptr);
	  int height = GetSystemMetrics(SM_CYSCREEN);
	  int width = GetSystemMetrics(SM_CXSCREEN);
	  memDc = CreateCompatibleDC(srcDc);
	  memBit = CreateCompatibleBitmap(srcDc, width, height);
	  auto kOldBitmap = (HBITMAP)SelectObject(memDc, memBit);
	  BitBlt(memDc, 0, 0, width, height, srcDc, 0, 0, SRCCOPY);

	  Gdiplus::Bitmap bitmap(memBit, nullptr);
	  CLSID clsId;

	  Screen::GetEncoderClsId(L"image/jpeg", &clsId);
	  std::wstring full = std::wstring(path.begin(), path.end()) + std::wstring(name.begin(), name.end());
	  std::wstring extension = L".jpeg";

	  std::wstringstream ss;
	  ss << full.c_str() << Screen::picId++ << extension;

	  bitmap.Save(ss.str().c_str(), &clsId);
	  SelectObject(memDc, kOldBitmap);
	  DeleteObject(memDc);
	  DeleteObject(memBit);
	  ReleaseDC(nullptr, srcDc);
	}
	GdiplusShutdown(gdiplusToken);
	Sleep(delay);
  }
}
