#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_SelectBar : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_SelectBar();
	~UI_SelectBar();

	// delete Function
	UI_SelectBar(const UI_SelectBar& _Other) = delete;
	UI_SelectBar(UI_SelectBar&& _Other) noexcept = delete;
	UI_SelectBar& operator=(const UI_SelectBar& _Other) = delete;
	UI_SelectBar& operator=(UI_SelectBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
};

