#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineRender;
class Effect_wall : public GameEngineActor
{
public:
	// constrcuter destructer
	Effect_wall();
	~Effect_wall();

	// delete Function
	Effect_wall(const Effect_wall& _Other) = delete;
	Effect_wall(Effect_wall&& _Other) noexcept = delete;
	Effect_wall& operator=(const Effect_wall& _Other) = delete;
	Effect_wall& operator=(Effect_wall&& _Other) noexcept = delete;

	GameEngineRender* GetRender() const
	{
		return m_AnimationRender;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* m_AnimationRender = nullptr;
};
