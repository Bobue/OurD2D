#pragma once
#include "Content.h"
#include "WindowController.h"

class GameContent : public Content
{
public:
	void OnStart(EngineContext& engine) override;
	void OnUpdate(EngineContext& engine, float deltaTime) override;
	void OnEnd(EngineContext& engine) override;


private:
	int mainWindowId = -1;
	float a = 0.1f, b = 0.1f;//그냥 임시로 창생성 보려고 만든거 나중에 삭제할거임!
	WindowController player; // 플레이어 컨트롤러(창) 객체
	WindowController enemy; // 적 컨트롤러(창) 객체
	BattleState state = BattleState::Explore; // 배틀 상태
};