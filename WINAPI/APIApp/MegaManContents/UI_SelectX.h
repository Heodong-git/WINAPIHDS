#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_SelectX : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_SelectX();
	~UI_SelectX();

	// delete Function
	UI_SelectX(const UI_SelectX& _Other) = delete;
	UI_SelectX(UI_SelectX&& _Other) noexcept = delete;
	UI_SelectX& operator=(const UI_SelectX& _Other) = delete;
	UI_SelectX& operator=(UI_SelectX&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

};

