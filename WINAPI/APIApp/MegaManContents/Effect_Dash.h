#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class GameEngineRender;
class Player_Zero;
class Effect_Dash : public GameEngineActor
{
	friend Player_Zero;

public:
	// constrcuter destructer
	Effect_Dash();
	~Effect_Dash();

	// delete Function
	Effect_Dash(const Effect_Dash& _Other) = delete;
	Effect_Dash(Effect_Dash&& _Other) noexcept = delete;
	Effect_Dash& operator=(const Effect_Dash& _Other) = delete;
	Effect_Dash& operator=(Effect_Dash&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* m_AnimationRender = nullptr;
};
