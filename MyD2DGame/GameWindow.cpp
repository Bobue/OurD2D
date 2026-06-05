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
		WS_POPUP | WS_BORDER | WS_DLGFRAME,
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

LRESULT CALLBACK GameWindow::StaticWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
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

LRESULT GameWindow::WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void GameWindow::ResizeWindowToMonitorRatio(HWND hwnd, double widthRatio, double heightRatio, double XRatio, double YRatio, bool flag)
{
	HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);

	MONITORINFO mi = {};
	mi.cbSize = sizeof(MONITORINFO);

	if (!GetMonitorInfo(hMonitor, &mi)) return;


	RECT work = mi.rcWork; //툴바 작업 표시줄 등등 제외한 영역

	//모니터 (작업공간의 너비 높이) 구하기
	int workWidth  = work.right  - work.left;
	int workHeight = work.bottom - work.top ;

	//모니터 작업공간의 (창의 너비, 높이) 구하기
	int targetWidth = static_cast<int>(workWidth * widthRatio);
	int targetHeight = static_cast<int>(workHeight * heightRatio);


	int locationWidth = static_cast<int>(workWidth * XRatio);
	int locationHeigh = static_cast<int>(workHeight * YRatio);

	if (flag ==false)
	{
		locationWidth -= targetWidth / 2;
		locationHeigh -= targetHeight / 2;
	}

	SetWindowPos(hwnd, nullptr, locationWidth, locationHeigh, targetWidth, targetHeight, SWP_NOZORDER | SWP_NOACTIVATE);
}