#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class ESelectPlayer
{
	X,
	ZERO
};

class UI_MainSelectUI : public GameEngineActor
{
	friend class SelectLevel;
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

	inline ESelectPlayer GetSelectPlayer()
	{
		return m_SelectPlayer;
	}

private:
	float4 m_ScreenSize = float4::Zero;
	float4 m_ScreenSizeHalf = float4::Zero;
	ESelectPlayer m_SelectPlayer = ESelectPlayer::X;

	float4 m_TopTextStartPos = float4::Zero;
	float4 m_BottomTextStartPos = float4::Zero;

	static float m_Time;
	float		 m_TextMoveTime = 7.5f; 
	float		 m_TextMoveSpeed = 300.0f;
	
	// 생성만하고 안가지고 있어도 될 것 같은 친구들인줄 알았는데 게임스타트 하면 얘네를 다 꺼줘야하는데.
	// 제로애니메이션, 백그라운드를 제외한 모든녀석을들 Off 해야함.
	GameEngineRender* m_SelectX = nullptr;
	GameEngineRender* m_SelectZero = nullptr;
	GameEngineRender* m_TextX = nullptr;
	GameEngineRender* m_TextZero = nullptr;

	// 가지고 있으면 편한 친구들
	GameEngineRender* m_SelectBar = nullptr;
	GameEngineRender* m_TopText = nullptr;
	GameEngineRender* m_BottomText = nullptr;
	GameEngineRender* m_ZeroAnimation = nullptr;

	void SelectUpdate(float _DeltaTime);
	void TopBottomTextUpdate(float _DeltaTime);
};

