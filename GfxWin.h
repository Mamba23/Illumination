#pragma once

#include "Win.h"

#include "WinBitmap.h"

// ���� � ���������� �����������
class GfxWindow: public Window
{

public:
	GfxWindow(int x, int y, int w, int h, const char* title);
	//~GfxWindow();

	void SetBuffer(unsigned char* Data) { Bmp.SetData(Data); }

	virtual void OnCreate();

	virtual void OnDestroy();

	virtual void OnSize(int NewW, int NewH);

	virtual void OnPaint();

	void DrawBackground(int color);

private:
	WinBitmap Bmp;	
};
