#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_SelectZero : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_SelectZero();
	~UI_SelectZero();

	// delete Function
	UI_SelectZero(const UI_SelectZero& _Other) = delete;
	UI_SelectZero(UI_SelectZero&& _Other) noexcept = delete;
	UI_SelectZero& operator=(const UI_SelectZero& _Other) = delete;
	UI_SelectZero& operator=(UI_SelectZero&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

};

