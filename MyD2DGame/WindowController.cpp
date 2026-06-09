
#include "WindowController.h"
#include "WindowManager.h"   


void WindowController::Initalize(EngineContext &engine)
{
	context = &engine;
}


void WindowController::CreatePlayerStartField() // 플레이어 필드
{
    auto& windows = context->GetWindowManager();
    playerFieldId = windows.CreateGameWindow({ 
        L"Player Field",
        0.5, 0.75,
        1.0, 0.5
        });
}
void WindowController::CreatePlayerStartRegion()
{
    auto& windows = context->GetWindowManager();

    playerRegionId = windows.CreateGameWindow( // 플레이어 지역
        {
            L"Main Window",
            0.5, 0.8,
            0.1, 0.15
        }
    );
}

void WindowController::CreateEnemyStartField() // 적 필드
{
    auto& windows = context->GetWindowManager();
    enemyFieldId = windows.CreateGameWindow({
        L"Enemy Field",
        0.5, 0.25,
        1.0, 0.5
        });
}
void WindowController::CreateEnemyStartRegion()
{
    auto& windows = context->GetWindowManager();
    enemyRegionId = windows.CreateGameWindow( // 적 지역
        {
            L"Main Window",
            0.5, 0.2,
            0.1, 0.15
        }
    );
}


void WindowController::MoveRegion()
{

}
void WindowController::ResizeField()
{

}