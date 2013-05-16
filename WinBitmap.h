#pragma once

#include <windows.h>

/// Представление Bitmap'а
class WinBitmap
{
public:
	WinBitmap()
	{
	}

	void CreateDCs(HDC SourceDC, int w1, int h1)
	{
	//	if (w1 < 0) w1 = 800;
	//	if (h1 < 0) h1 = 600;
		Width  = w1;
		Height = h1;

		// создаём временный контекст
		hMemDC = CreateCompatibleDC(SourceDC);

		// создаём совместимую картинку
		hTmpBmp = CreateCompatibleBitmap(SourceDC, BitMapWidth, BitMapHeight);

		memset(&BitmapInfo.bmiHeader, 0, sizeof(BITMAPINFOHEADER));

		BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		BitmapInfo.bmiHeader.biWidth = BitMapWidth;
		BitmapInfo.bmiHeader.biHeight = BitMapHeight;
		BitmapInfo.bmiHeader.biPlanes = 1;
		BitmapInfo.bmiHeader.biBitCount = 24;
		BitmapInfo.bmiHeader.biCompression = 0;
		BitmapInfo.bmiHeader.biSizeImage = BitMapWidth * BitMapHeight * 24;
	}

	void DestroyDCs()
        {
		// чистим всё
		DeleteDC(hMemDC);
		DeleteObject(hTmpBmp);
        }

	~WinBitmap()
	{
		DestroyDCs();
	}

	void SetData(BYTE* Data)
	{
		// копирум содержимое Img[] в наш BITMAP

		SetDIBits(hMemDC, hTmpBmp, 0, BitMapHeight, Data, &BitmapInfo, DIB_RGB_COLORS);
		
	}

	void Blit(HDC Where, int x, int y)
	{
		// выбираем BITMAP на hMemDC
		SelectObject(hMemDC, hTmpBmp);

		// копируем кусок контекста hMemDC (там выбран BITMAP) на "экран" dc
		BitBlt(Where,0,0,Width,Height,hMemDC, 0, 0, SRCCOPY);

	}

	void Stretch(HDC Where, int x, int y) {

		SelectObject(hMemDC, hTmpBmp);
		SetStretchBltMode(Where, COLORONCOLOR);
		StretchBlt(Where, x, y, Width, Height, hMemDC, 0, 0, BitMapWidth, BitMapHeight, SRCCOPY);
	}


private:
	/// размеры
	int Width, Height;

	static int BitMapWidth, BitMapHeight;

	/// временный контекст
	HDC hMemDC;

	/// картинка
	HBITMAP hTmpBmp;

	/// информация о картинке
	BITMAPINFO BitmapInfo;
};
