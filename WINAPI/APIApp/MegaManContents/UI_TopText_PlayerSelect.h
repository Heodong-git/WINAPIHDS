#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 탑으로 변경
class UI_TopText_PlayerSelect : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_TopText_PlayerSelect();
	~UI_TopText_PlayerSelect();

	// delete Function
	UI_TopText_PlayerSelect(const UI_TopText_PlayerSelect& _Other) = delete;
	UI_TopText_PlayerSelect(UI_TopText_PlayerSelect&& _Other) noexcept = delete;
	UI_TopText_PlayerSelect& operator=(const UI_TopText_PlayerSelect& _Other) = delete;
	UI_TopText_PlayerSelect& operator=(UI_TopText_PlayerSelect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	static float Time;
	float MoveSpeed = 400.0f;
	float4 OriginPos = float4::Zero;
	GameEngineRender* AnimationRender = nullptr;

};

