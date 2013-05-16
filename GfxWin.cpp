#include "GfxWin.h"

#include "App.h"

GfxWindow::GfxWindow(int x, int y, int w, int h, const char* title)
{
	InitWithParams(App::szWinName, x, y, w, h, title);
	OnSize(w, h);
}


void GfxWindow::OnCreate()
{
}


void GfxWindow::OnDestroy()
{
	Bmp.DestroyDCs();
}


void GfxWindow::OnSize(int NewW, int NewH)
{
	Bmp.DestroyDCs();

	HDC h = this->GetDC();

	Bmp.CreateDCs(h, NewW, NewH);

	Width = NewW;

	Height = NewH;

	ReleaseDC(this->GetHandle(), h);
	InvalidateRect(GetHandle(),NULL,NULL);
}


void GfxWindow::DrawBackground(int color) {
		
	HDC h = this->GetDC();
	RECT rect;
	SetRect(&rect,0,0,GetWidth(),GetHeight());
	COLORREF colorref = RGB((color >> 16) & 0xFF,(color >> 8) & 0xFF, color & 0xFF);
	HBRUSH brush = CreateSolidBrush(colorref);
	FillRect(h,&rect,brush);
	ReleaseDC(GetHandle(),h);

}


void GfxWindow::OnPaint()
{
	HDC h = this->GetDC();

//	Bmp.Blit(h, 0, 0);
	Bmp.Stretch(h, 0, 0);
	ReleaseDC(this->GetHandle(), h);
}
