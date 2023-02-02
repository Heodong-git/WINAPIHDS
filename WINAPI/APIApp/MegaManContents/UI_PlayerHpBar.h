#pragma once
#include <GameEngineCore/GameEngineActor.h>


class GameEngineRender;
class UI_PlayerHpBar: public GameEngineActor
{
public:
	// constrcuter destructer
	UI_PlayerHpBar();
	~UI_PlayerHpBar();

	// delete Function
	UI_PlayerHpBar(const UI_PlayerHpBar& _Other) = delete;
	UI_PlayerHpBar(UI_PlayerHpBar&& _Other) noexcept = delete;
	UI_PlayerHpBar& operator=(const UI_PlayerHpBar& _Other) = delete;
	UI_PlayerHpBar& operator=(UI_PlayerHpBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* m_AnimationRender = nullptr;
};

