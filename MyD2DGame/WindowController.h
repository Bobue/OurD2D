#pragma once
#include "EngineContext.h"

enum class BattleState
{
	Explore, // 탐색
	Battle, // 배틀 중
	Return // 자리로 돌아가는 중
};

class WindowController
{
public:
	void Initalize(EngineContext& engine);
	// 플레이어 창 위치 수정
	void CreatePlayerStartField();
	void CreatePlayerStartRegion();

	// 적 창 위치 수정
	void CreateEnemyStartField();
	void CreateEnemyStartRegion();

	void MovePlayerRegion(float deltatime);
	void ResizeField();


	// 적 전투 돌입 시 enemy field 제거 player field 크기 제어
	void BattleRegion(float deltaTime, int enemyRegionId);
	int GetEnemyRegionId() const { return enemyRegionId; };
	// 적 전투 종료 시 제자리로 복귀
	void ResetExplore();
	int GetPlayerRegionId() const { return playerRegionId; }


private:
	EngineContext* context = nullptr;
	int playerFieldId = -1;
	int playerRegionId = -1;
	int enemyFieldId = -1;
	int enemyRegionId = -1;


	float battleRegionCompareX = 0.0f;
	float battleRegionCompareY = 0.0f;
	float currentOffsetX = 0.0f;
	float currentOffsetY = 0.0f;
};