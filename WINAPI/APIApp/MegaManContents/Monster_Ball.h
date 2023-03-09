#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class GameEngineRender;
class GameEngineCollision;
class Monster_Ball : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster_Ball();
	~Monster_Ball();

	// delete Function
	Monster_Ball(const Monster_Ball& _Other) = delete;
	Monster_Ball(Monster_Ball&& _Other) noexcept = delete;
	Monster_Ball& operator=(const Monster_Ball& _Other) = delete;
	Monster_Ball& operator=(Monster_Ball&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* m_Collider = nullptr;
	static float Time;

	GameEngineSoundPlayer m_Sound;
	
	float m_MoveSpeed = 500.0f;
	float m_Range = 800.0f;
};

