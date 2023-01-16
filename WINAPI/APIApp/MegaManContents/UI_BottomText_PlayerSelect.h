#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 탑으로 변경
class UI_BottomText_PlayerSelect : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_BottomText_PlayerSelect();
	~UI_BottomText_PlayerSelect();

	// delete Function
	UI_BottomText_PlayerSelect(const UI_BottomText_PlayerSelect& _Other) = delete;
	UI_BottomText_PlayerSelect(UI_BottomText_PlayerSelect&& _Other) noexcept = delete;
	UI_BottomText_PlayerSelect& operator=(const UI_BottomText_PlayerSelect& _Other) = delete;
	UI_BottomText_PlayerSelect& operator=(UI_BottomText_PlayerSelect&& _Other) noexcept = delete;

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

