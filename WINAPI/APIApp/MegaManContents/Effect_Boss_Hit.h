#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Effect_Boss_Hit : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Boss_Hit();
	~Effect_Boss_Hit();

	// delete Function
	Effect_Boss_Hit(const Effect_Boss_Hit& _Other) = delete;
	Effect_Boss_Hit(Effect_Boss_Hit&& _Other) noexcept = delete;
	Effect_Boss_Hit& operator=(const Effect_Boss_Hit& _Other) = delete;
	Effect_Boss_Hit& operator=(Effect_Boss_Hit&& _Other) noexcept = delete;

	GameEngineRender* GetEffectRender() const
	{
		return m_EffectRender;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineRender* m_EffectRender = nullptr;
};
