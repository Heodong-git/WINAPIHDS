#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UI_MainSelectUI : public GameEngineActor
{
public:
	// constrcuter destructer
	UI_MainSelectUI();
	~UI_MainSelectUI();

	// delete Function
	UI_MainSelectUI(const UI_MainSelectUI& _Other) = delete;
	UI_MainSelectUI(UI_MainSelectUI&& _Other) noexcept = delete;
	UI_MainSelectUI& operator=(const UI_MainSelectUI& _Other) = delete;
	UI_MainSelectUI& operator=(UI_MainSelectUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* m_SelectX = nullptr;
	GameEngineRender* m_SelectZero = nullptr;

	GameEngineRender* m_TextX = nullptr;
	GameEngineRender* m_TextZero = nullptr;

	GameEngineRender* m_SelectBar = nullptr;
};

