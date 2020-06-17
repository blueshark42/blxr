#include <iostream>
#include "screen.h"

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

  for (UINT j = 0; j < encSize; ++j) {
	if (wcscmp(imageCodecInfo[j].MimeType, format) == 0) {
	  *clsId = imageCodecInfo[j].Clsid;
	  free(imageCodecInfo);
	  return j;
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
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
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

	  Gdiplus::Bitmap bitmap(memBit, NULL);
	  CLSID clsId;

	  Screen::GetEncoderClsId(L"image/jpeg", &clsId);
	  std::wstring full = std::wstring(path.begin(), path.end())
		  + std::wstring(name.begin(), name.end());
	  const WCHAR *fullName = full.c_str() + picId;

	  bitmap.Save(fullName, &clsId);

	  SelectObject(memDc, kOldBitmap);
	  DeleteObject(memDc);
	  DeleteObject(memBit);
	  ReleaseDC(NULL, srcDc);
	}
	GdiplusShutdown(gdiplusToken);
	picId++;
	std::cout << picId << std::endl;
	Sleep(delay);
  }
}
