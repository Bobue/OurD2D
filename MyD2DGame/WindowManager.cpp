#include "WindowManager.h"

bool WindowManager::Initialize(HINSTANCE hInstance)
{
	this->hInstance = hInstance;

	WNDCLASSW wc{};
	wc.lpfnWndProc = WindowManager::WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	
	if (RegisterClassW(&wc) == 0)
	{
		return false;
	}

	return true;
}

int WindowManager::CreateGameWindow(const WindowCreateInfo& info)
{
	const int newId = nextWindowId++;
	auto window = std::make_unique<GameWindow>();

	if (!window->Create(hInstance, className, newId, info))
	{
		return -1;
	}

	windows.push_back(std::move(window));

	return newId;
}

GameWindow* WindowManager::GetWindowById(int id)
{
	for (auto& window : windows)
	{
		if (window->GetID() == id)
		{
			return window.get();
		}
	}

	return nullptr;
}

LRESULT CALLBACK WindowManager::WindowProc(
	HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProcW(hwnd, message, wParam, lParam);
	}
}