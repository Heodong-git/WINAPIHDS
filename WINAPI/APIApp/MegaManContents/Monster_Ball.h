#pragma once
#include <GameEngineCore/GameEngineActor.h>

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
	static float Time;
	
};

