#pragma once
#include <Windows.h>

class OverlayWindow
{
public:
	static constexpr COLORREF TransparentColor = RGB(255, 0, 255);

	bool Create(HINSTANCE hInstance);
	HWND GetHwnd()  const;

	int GetX()      const;
	int GetY()	    const;
	int GetWidth()  const;
	int GetHeight() const;

private:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HWND hwnd = nullptr;
	int x	   = 0;
	int y	   = 0;
	int width  = 0;
	int height = 0;
};