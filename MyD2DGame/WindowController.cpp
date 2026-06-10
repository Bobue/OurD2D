
#include "WindowController.h"
#include "WindowManager.h"   
#include "InputManager.h"


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


void WindowController::MovePlayerRegion(float deltaTime)
{
    auto& input = context->GetInputManager();
    auto& windows = context->GetWindowManager();
   /* if (input.IsKeyPressed(playerRegionId, VK_LEFT))
    {
        int playerFieldId = windows.CreateGameWindow(
            {
                L"Add Window",
                x, y,
                0.2, 0.2
            }
        );
        x  += 0.01; y+= 0.01;
    }*/
    
    if (input.IsKeyDown(playerRegionId, VK_UP))
    {
        windows.GetWindowById(playerRegionId)->MoveWindow(0.0, -0.15, 1.3, deltaTime);
    }
    if (input.IsKeyDown(playerRegionId, VK_DOWN))
    {
        windows.GetWindowById(playerRegionId)->MoveWindow(0.0, 0.15, 1.3, deltaTime);
    }
    if (input.IsKeyDown(playerRegionId, VK_LEFT))
    {
        windows.GetWindowById(playerRegionId)->MoveWindow(-0.15, 0, 1.3, deltaTime);
    }
    if (input.IsKeyDown(playerRegionId, VK_RIGHT))
    {
        windows.GetWindowById(playerRegionId)->MoveWindow(0.15, 0.0, 1.3, deltaTime);
    }
    if (input.IsKeyPressed(playerRegionId, VK_SPACE))
    {
        windows.GetWindowById(playerRegionId)->MoveWindow(0, -40.0, 1, deltaTime);
    }
}


void WindowController::ResizeField()
{
    auto& input = context->GetInputManager();
    auto& windows = context->GetWindowManager();

    if (input.IsKeyPressed(playerRegionId, VK_SHIFT))
    {
        windows.GetWindowById(playerRegionId)->ReSizeWindow(0.1, 0.1);
    }
    if (input.IsKeyPressed(playerRegionId, VK_TAB))
    {
        windows.GetWindowById(playerRegionId)->ReSizeWindow(0.8, 0.8);
    }
}

void WindowController::BattleRegion(float deltaTime, int enemyRegionId)
{
    auto& windows = context->GetWindowManager();

    auto* playerWnd = windows.GetWindowById(playerRegionId);
    auto* enemyWnd = windows.GetWindowById(enemyRegionId);

    if (playerWnd == nullptr || enemyWnd == nullptr) return;

    // 목표 위치 (적 region 시작 위치)
    float targetX = enemyWnd->GetX();
    float targetY = enemyWnd->GetY();

    float currentX = playerWnd->GetX();
    float currentY = playerWnd->GetY();

    float diffX = targetX - currentX;
    float diffY = targetY - currentY;

    // 목표 위치에 충분히 가까우면 멈춤
    if (abs(diffX) < 5.0f && abs(diffY) < 5.0f) return;

    // 방향 계산해서 이동
    HMONITOR hMonitor = MonitorFromWindow(playerWnd->GetHwnd(), MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = {};
    mi.cbSize = sizeof(MONITORINFO);
    if (!GetMonitorInfo(hMonitor, &mi)) return;

    int workWidth = mi.rcWork.right - mi.rcWork.left;
    int workHeight = mi.rcWork.bottom - mi.rcWork.top;

    float ratioX = diffX / workWidth;
    float ratioY = diffY / workHeight;

    playerWnd->MoveWindow(ratioX, ratioY, 3.0f, deltaTime);
}

void WindowController::ResetExplore()
{
    battleRegionCompareY = 0.0f;
}
