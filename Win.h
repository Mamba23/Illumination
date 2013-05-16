#pragma once
#include <iostream>
#include <windows.h>

// просто окно
class Window
{
public:
	Window();

	Window(int x, int y, int w, int h, const char* title);

	~Window();

	void InitWithParams(const char* WndClass, int x, int y, int w, int h, const char* title);

	void Init(const char* WndClass);

	void Repaint();

	void SetTitle(const char* title);

	void SetPos(int x, int y);

	void SetSize(int w, int h);

	void Show(bool Visible);

	int GetWidth() const { 
		return Width; 
	}
	int GetHeight() const { 
		return Height; 
	}

	// события

	// квант времени
	void SetDelta(float dt);

	virtual void OnCreate() {}

	virtual void OnDestroy() {}

	virtual void OnPaint() {}

	virtual void OnSize(int NewW, int NewH) {}

	virtual void OnMouseDown(int Button, int x, int y) {}

	virtual void OnMouseUp(int Button, int x, int y) {}

	virtual void OnMouseMove(int x, int y) {}

	virtual void OnKeyDown(int key) {}

	virtual void OnKeyUp(int key) {}

	virtual void OnTimer() { 
		//std::cout << "Time = " << LocalTime << std::endl;
		LocalTime += DeltaTime;
	}

	//virtual void OffTimer() { DeltaTime = 0; }

	virtual void OnWheelUp() {}

	virtual void OnWheelDown() {}
	
	virtual void OnCommand(int lParam, int wParam) {}

	HDC GetDC() { return ::GetDC(hWnd); }

	HWND GetHandle() { return hWnd; }

	void  SetTime (float time);

	float GetTime() const { return LocalTime; }
	
	void StopTime (float time, int idTimer);


protected:
	int Width, Height;
private:

	float DeltaTime;

	float LocalTime;

	HWND hWnd;
};
