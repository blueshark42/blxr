#include "screen.h"
int screen::GetEncoderClsId(const WCHAR *format, CLSID *cls_id) {
  using namespace Gdiplus;
  UINT num = 0;
  UINT size = 0;

  ImageCodecInfo*pImageCodecInfo = nullptr;

  GetImageEncodersSize(&num, &size);
  if (size==0)
	return -1;

  pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
  if (pImageCodecInfo==nullptr)
	return -1;

  GetImageEncoders(num, size, pImageCodecInfo);
  for (UINT j = 0; j < num; ++j) {
	if (wcscmp(pImageCodecInfo[j].MimeType, format)==0) {
	  *cls_id = pImageCodecInfo[j].Clsid;
	  free(pImageCodecInfo);
	  return j;
	}
  }
  free(pImageCodecInfo);
  return 0;
}

bool screen::CaptureScreen() {
  using namespace Gdiplus;
  IStream *istream;
  HRESULT res = CreateStreamOnHGlobal(nullptr, true, &istream);
  GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;
  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
  {
	HDC scrdc, memdc;
	HBITMAP membit;
	scrdc = ::GetDC(0);
	int Height = GetSystemMetrics(SM_CYSCREEN);
	int Width = GetSystemMetrics(SM_CXSCREEN);
	memdc = CreateCompatibleDC(scrdc);
	membit = CreateCompatibleBitmap(scrdc, Width, Height);
	HBITMAP old_bitmap = (HBITMAP)SelectObject(memdc, membit);
	BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);

	Bitmap bitmap(membit, nullptr);
	CLSID cls_id;
	GetEncoderClsId(L"image/jpeg", &cls_id);
	//bitmap.Save(L"screen.jpeg", &cls_id, NULL); // To save the jpeg to a file
	bitmap.Save(istream, &cls_id, nullptr);

	// Create a bitmap from the stream and save it to make sure the stream has the image
	//Gdiplus::Bitmap bmp(istream, NULL);
	//bmp.Save(L"t1est.jpeg", &cls_id, NULL);
	// END

	delete &cls_id;
	DeleteObject(memdc);
	DeleteObject(membit);
	ReleaseDC(nullptr, scrdc);
  }
  GdiplusShutdown(gdiplusToken);
  istream->Release();
  return true;
}