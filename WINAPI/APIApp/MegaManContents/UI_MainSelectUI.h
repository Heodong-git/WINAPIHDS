#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class ESelectPlayer
{
	X,
	ZERO
};

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
	float4 m_ScreenSize = float4::Zero;
	float4 m_ScreenSizeHalf = float4::Zero;
	ESelectPlayer m_SelectPlayer = ESelectPlayer::X;
	
	// 생성만하고 안가지고 있어도 될 것 같은 친구들
	GameEngineRender* m_SelectX = nullptr;
	GameEngineRender* m_SelectZero = nullptr;
	GameEngineRender* m_TextX = nullptr;
	GameEngineRender* m_TextZero = nullptr;

	// 가지고 있으면 편한 친구들
	GameEngineRender* m_SelectBar = nullptr;
	GameEngineRender* m_TopText = nullptr;
	GameEngineRender* m_BottomText = nullptr;

	void SelectUpdate(float _DeltaTime);
	void TopBottomTextUpdate(float _DeltaTime);
};

