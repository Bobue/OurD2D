#pragma once


class WindowManager;

class EngineContext
{
public:
	EngineContext(WindowManager& windowManager);

	WindowManager& GetWindowManager();

private:
	WindowManager& windowManager;
};