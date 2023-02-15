#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

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
	GameEngineSoundPlayer m_SelectSound;

	float4 m_ScreenSize = float4::Zero;
	float4 m_ScreenSizeHalf = float4::Zero;
	ESelectPlayer m_SelectPlayer = ESelectPlayer::X;

	float4 m_TopTextStartPos = float4::Zero;
	float4 m_BottomTextStartPos = float4::Zero;

	static float m_Time;
	float		 m_TextMoveTime = 7.5f; 
	float		 m_TextMoveSpeed = 300.0f;
	
	// �������ϰ� �Ȱ����� �־ �� �� ���� ģ�������� �˾Ҵµ� ���ӽ�ŸƮ �ϸ� ��׸� �� ������ϴµ�.
	// ���ξִϸ��̼�, ��׶��带 ������ ���༮���� Off �ؾ���.
	GameEngineRender* m_SelectX = nullptr;
	GameEngineRender* m_SelectZero = nullptr;
	GameEngineRender* m_TextX = nullptr;
	GameEngineRender* m_TextZero = nullptr;

	// ������ ������ ���� ģ����
	GameEngineRender* m_SelectBar = nullptr;
	GameEngineRender* m_TopText = nullptr;
	GameEngineRender* m_BottomText = nullptr;
	GameEngineRender* m_ZeroAnimation = nullptr;

	bool			  m_Select = false;

	void SelectUpdate(float _DeltaTime);
	void TopBottomTextUpdate(float _DeltaTime);
};

