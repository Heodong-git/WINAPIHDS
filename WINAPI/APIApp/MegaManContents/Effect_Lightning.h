#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineRender;
class GameEngineCollision;
class Effect_Lightning : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_Lightning();
	~Effect_Lightning();

	// delete Function
	Effect_Lightning(const Effect_Lightning& _Other) = delete;
	Effect_Lightning(Effect_Lightning&& _Other) noexcept = delete;
	Effect_Lightning& operator=(const Effect_Lightning& _Other) = delete;
	Effect_Lightning& operator=(Effect_Lightning&& _Other) noexcept = delete;

	GameEngineRender* GetRender() const
	{
		return m_AnimationRender;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender*	 m_AnimationRender = nullptr;
	GameEngineCollision* m_Collider = nullptr;

	float				 m_LiveTime = 1.0f;
};
