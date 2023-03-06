#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineRender;
class Player_Zero;

class Effect_Explosion : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Explosion();
	~Effect_Explosion();

	// delete Function
	Effect_Explosion(const Effect_Explosion& _Other) = delete;
	Effect_Explosion(Effect_Explosion&& _Other) noexcept = delete;
	Effect_Explosion& operator=(const Effect_Explosion& _Other) = delete;
	Effect_Explosion& operator=(Effect_Explosion&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* m_AnimationRender = nullptr;
};
