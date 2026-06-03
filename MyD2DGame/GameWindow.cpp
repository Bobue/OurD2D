#include "GameWindow.h"

GameWindow::GameWindow() :m_hwnd(nullptr), m_hInstance(nullptr)
{

}

GameWindow::~GameWindow()
{

}

bool GameWindow::Create(
						HINSTANCE hInstance,
						const wchar_t* title,
						int x,     int y,
						int width, int height
)
{
	m_hInstance = hInstance;

	const wchar_t* className = L"GameWindowClass";

	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = GameWindow::StaticWndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);

	static bool registered = false;

	if (!registered)
	{
		if (!RegisterClassEx(&wc))
		{
			return false;
		}

		registered = true;
	}

	m_hwnd = CreateWindowEx(
		0, className, title,
		WS_OVERLAPPEDWINDOW,
		x,y,
		width, height,
		nullptr, nullptr,
		hInstance, this
	);

	return m_hwnd != nullptr;
}

void GameWindow::Show(int nCmdShow)
{
	ShowWindow(m_hwnd, nCmdShow);
	UpdateWindow(m_hwnd);
}

HWND GameWindow::GetHwnd() const
{
	return m_hwnd;
}

LRESULT CALLBACK GameWindow::StaticWndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	GameWindow* window = nullptr;

	if (msg == WM_NCCREATE)
	{
		CREATESTRUCT* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);

		window = reinterpret_cast<GameWindow*>(createStruct->lpCreateParams);

		SetWindowLongPtr(
			hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window)
		);
	}
	else
	{
		window = reinterpret_cast<GameWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (window)
	{
		return window->WndProc(hwnd, msg, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT GameWindow::WndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}