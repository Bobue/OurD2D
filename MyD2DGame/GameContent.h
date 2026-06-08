#pragma once
#include "Content.h"
#include <d2d1.h>
#include<wrl/client.h>


class GameContent : public Content
{
public:
	void OnStart(EngineContext& engine) override;
	void OnUpdate(EngineContext& engine, float deltaTime) override;
	void OnRender(EngineContext& engine) override;
	void OnEnd(EngineContext& engine) override;


private:
	int mainWindowId = -1;
	Microsoft::WRL::ComPtr<ID2D1Bitmap> testBitmap;
	float a = 0.1f, b = 0.1f;//그냥 임시로 창생성 보려고 만든거 나중에 삭제할거임!
};