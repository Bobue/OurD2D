#include "GameContent.h"

#include "EngineContext.h"
#include "WindowManager.h"

void GameContent::OnStart(EngineContext& engine)
{
	auto& windows = engine.GetWindowManager();

	int mainWindow = windows.CreateGameWindow(
		{
			L"Main Window",
			100, 100,
			500, 400
		}
	);

	int subWindow = windows.CreateGameWindow(
		{
			L"Sub Window",
			500, 100,
			500, 400
		}
	);
}
void GameContent::OnUpdate(EngineContext& engine, float deltaTime)
{
}

void GameContent::OnEnd(EngineContext& engine)
{
}