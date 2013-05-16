#pragma once

#include <windows.h>

#include <map>
#include <vector>

class Window;

class App
{
public:
	App() { Init(); }

	// ����������� ������ � ������ ��������������� ����
	int Init();

	// ������ ����� ��������� ���������
	int Run();

	// ������ �� �����
	void Exit();

	// ������� ����
	void SetMainWindow(Window* W) { MainWnd = W; }

	/// ��� �������� ������ �� ���������
	static const char* szWinName;

private:
	static LRESULT CALLBACK MyFunc(HWND, UINT, WPARAM, LPARAM);

	// ������� ���� (���� �������� WM_DESTROY)
	Window* MainWnd;
};