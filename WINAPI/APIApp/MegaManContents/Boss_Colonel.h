#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>


enum class BOSSSTATE
{
	START,
	IDLE,
	FIRST_ATTACK,
	SECOND_ATTACK,
	TELEPORT,
	LIGHTNING_PATTERN,
	DEATH,
	NONE,
};


class GameEngineRender;
class GameEngineCollision;
class UI_PlayerHpBar;
class Boss_Colonel : public GameEngineActor
{
	friend class UI_PlayerHpBar;

public:
	// constrcuter destructer
	Boss_Colonel();
	~Boss_Colonel();

	// delete Function
	Boss_Colonel(const Boss_Colonel& _Other) = delete;
	Boss_Colonel(Boss_Colonel&& _Other) noexcept = delete;
	Boss_Colonel& operator=(const Boss_Colonel& _Other) = delete;
	Boss_Colonel& operator=(Boss_Colonel&& _Other) noexcept = delete;

	inline int GetHp()
	{
		return m_Hp;
	}

	inline void Damage(int _Damage)
	{
		m_Hp -= _Damage;
	}

	bool IsHpZero()
	{
		return m_Hp == 0;
	}

	inline void SetHpBar(UI_PlayerHpBar* _UI)
	{
		m_HpBar = _UI;
	}

	inline GameEngineCollision* GetCollider()
	{
		return m_Collider;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float  m_InvincibilityTime = 0.0f;
	float  m_MaxInvincibility = 0.45f;
	int	   m_Hp = 10;
	
	bool   m_SkillUse = false;

	float   m_SkillCoolDown = 3.0f;
	float   m_SkillCoolDownMax = 3.0f;

	bool   m_Lightning = false;

	
	GameEngineSoundPlayer m_Sound;

	UI_PlayerHpBar* m_HpBar = nullptr;
	bool		  m_Invincibility = false;
	std::string  m_DirString = "Left_";
	GameEngineRender* m_AnimationRender = nullptr;

	GameEngineCollision* m_Collider = nullptr;
	GameEngineCollision* m_AttackCollider = nullptr;

	BOSSSTATE m_PrevState = BOSSSTATE::START;
	BOSSSTATE m_CurState = BOSSSTATE::START;
	BOSSSTATE m_NextState = BOSSSTATE::START;

	void AnimDirCheck(const std::string_view& _AnimationName);

	void ChangeState(BOSSSTATE _State);
	void UpdateState(float _DeltaTime);


	void AnimationCreate();

	void Start_Start();
	void Start_Update(float _DeltaTime);
	void Start_End(); 

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Teleport_Start();
	void Teleport_Update(float _DeltaTime);
	void Teleport_End();

	void First_Attack_Start();
	void First_Attack_Update(float _DeltaTime);
	void First_Attack_End();

	void Second_Attack_Start();
	void Second_Attack_Update(float _DeltaTime);
	void Second_Attack_End();

	void First_Pattern_Start();
	void First_Pattern_Update(float _DeltaTime);
	void First_Pattern_End();
	
	void Death_Start();
	void Death_Update(float _DeltaTime);
	void Death_End();
};

