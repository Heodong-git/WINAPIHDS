#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineRender;
class Player_Zero;
class Effect_Hit : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Hit();
	~Effect_Hit();

	// delete Function
	Effect_Hit(const Effect_Hit& _Other) = delete;
	Effect_Hit(Effect_Hit&& _Other) noexcept = delete;
	Effect_Hit& operator=(const Effect_Hit& _Other) = delete;
	Effect_Hit& operator=(Effect_Hit&& _Other) noexcept = delete;

	GameEngineRender* GetHitRender() const
	{
		return m_HitRender;
	}

	GameEngineRender* GetBossHitRender() const
	{
		return m_BossHitRender;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* m_HitRender = nullptr;
	GameEngineRender* m_BossHitRender = nullptr;

};
