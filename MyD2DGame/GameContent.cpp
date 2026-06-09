#include "GameContent.h"
#include "EngineContext.h"
#include "WindowManager.h"
#include "InputManager.h"  

#include <Windows.h>

void GameContent::OnStart(EngineContext& engine)
{
	player.Initalize(engine);
	enemy.Initalize(engine);

	player.CreatePlayerStartField();
	player.CreatePlayerStartRegion();

	enemy.CreateEnemyStartField();
	enemy.CreateEnemyStartRegion();
}

void GameContent::OnUpdate(EngineContext& engine, float deltaTime)
{
	auto& input = engine.GetInputManager();

	auto& windows = engine.GetWindowManager();

	//테스트용 


	switch (state) {
	case BattleState::Explore:
		player.MovePlayerRegion(deltaTime);
		if (input.IsKeyPressed(player.GetPlayerRegionId(), VK_RETURN))
		{
			player.ResetExplore();
			state = BattleState::Battle;
		}
		break;
	case BattleState::Battle:
		player.BattleRegion(deltaTime, enemy.GetEnemyRegionId());
		break;
	case BattleState::Return:
		// 미구현
		break;
	}

	//player.ResizeField();

}

void GameContent::OnEnd(EngineContext& engine)
{

}
