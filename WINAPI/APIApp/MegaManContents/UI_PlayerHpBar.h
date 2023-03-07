#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class HPSTATE
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	MAX,
};

class GameEngineRender;
class Player_Zero;
class Boss_Colonel;
class UI_PlayerHpBar: public GameEngineActor
{
public:
	// constrcuter destructer
	UI_PlayerHpBar();
	~UI_PlayerHpBar();

	// delete Function
	UI_PlayerHpBar(const UI_PlayerHpBar& _Other) = delete;
	UI_PlayerHpBar(UI_PlayerHpBar&& _Other) noexcept = delete;
	UI_PlayerHpBar& operator=(const UI_PlayerHpBar& _Other) = delete;
	UI_PlayerHpBar& operator=(UI_PlayerHpBar&& _Other) noexcept = delete;

	void SetPlayer(Player_Zero* _Player)
	{
		m_Player = _Player;
	}

	void SetBoss(Boss_Colonel* _Boss)
	{
		m_Boss = _Boss;
	}

	GameEngineRender* GetBossHpRender()
	{
		return m_BossHpRender;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* m_PlayerHpRender = nullptr;
	GameEngineRender* m_BossHpRender = nullptr;
	Player_Zero* m_Player = nullptr;
	Boss_Colonel* m_Boss = nullptr;

	void PlayerHpCheck();
	void BossHpCheck();
};

