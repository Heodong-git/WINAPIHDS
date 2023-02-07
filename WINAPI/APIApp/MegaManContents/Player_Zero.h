#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

enum class STATEVALUE
{
	NONE,		 // �ʱ�ȭ
	RECALL,		 // ���� (������)
	IDLE,		 // ���̵� 
	MOVE,		 // �̵�
	JUMP,		 // ����
	FALL,	     // ����
	FALL_END,	 // ��������
	ATTACK_FIRST,		 // ����
	ATTACK_SECOND,
	ATTACK_THIRD,
	DASH,		 // �뽬 
	JUMP_ATTACK,
};

class GameEngineCollision;
class Player_Zero : public GameEngineActor
{
public:
	// constrcuter destructer
	Player_Zero();
	~Player_Zero();

	// delete Function
	Player_Zero(const Player_Zero& _Other) = delete;
	Player_Zero(Player_Zero&& _Other) noexcept = delete;
	Player_Zero& operator=(const Player_Zero& _Other) = delete;
	Player_Zero& operator=(Player_Zero&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	// ����׿� ����
	bool		 m_DebugMode = false;

	float	     m_MoveSpeed = 1100.0f;
	bool		 m_Jump = false;
	bool	     m_Falling = false;
	float	     m_JumpTime = 0.0f;       // ��.. 
	float		 m_MaxJumpTime = 1.5f;
	float		 m_JumpPower = 600.0f;
	float	     m_GravityPower = 200.0f; // Gravity
	bool		 IsJumpMax = false;

	float		 m_DashPower = 1000.0f;
	float		 m_DashTime = 0.0f;
	float		 m_MaxDashTime = 1.0f;

	bool		 m_Ground = false;
	bool		 m_Gravity = true;
	std::string  m_DirString = "Right_";
	float4		 m_MoveDir = float4::Zero;

	// �÷��̾��� �⺻���´� ���̵�� �ʱ�ȭ
	STATEVALUE  m_StateValue = STATEVALUE::NONE;
	STATEVALUE  m_PrevState = STATEVALUE::NONE;
	STATEVALUE  m_NextState = STATEVALUE::NONE;
 
	GameEngineRender* m_AnimationRender = nullptr;
	GameEngineCollision* m_Collider = nullptr;
	GameEngineCollision* m_SaberCollider = nullptr;
	
	// ����׿�
	inline void DebugSwitch()
	{
		m_DebugMode = !m_DebugMode;
	}

	// ����üũ + �ִϸ��̼� ���� 
	void AnimDirCheck(const std::string_view& _AnimationName);
	void ChangeState(STATEVALUE _State);

	void PlayerCreateAnimation();

	// ���� ������Ʈ 
	void UpdateState(float _DeltaTime);
	// �÷��̾� �̵� ����
	void Movecalculation(float _DeltaTime);

	// ����
	void Recall_Start();
	void Recall_Update(float _DeltaTime);
	void Recall_End();

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Move_Start();
	void Move_Update(float _DeltaTime);
	void Move_End();

	void Jump_Start();
	void Jump_Update(float _DeltaTime);
	void Jump_End();

	void Fall_Start();
	void Fall_Update(float _DeltaTime);
	void Fall_End();

	void Fall_End_Start();
	void Fall_End_Update(float _DeltaTime);
	void Fall_End_End();

	void Attack_First_Start();
	void Attack_First_Update(float _DeltaTime);
	void Attack_First_End();

	void Attack_Second_Start();
	void Attack_Second_Update(float _DeltaTime);
	void Attack_Second_End();

	void Attack_Third_Start();
	void Attack_Third_Update(float _DeltaTime);
	void Attack_Third_End();

	void Dash_Start();
	void Dash_Update(float _DeltaTime);
	void Dash_End();

	void Jump_Attack_Start();
	void Jump_Attack_Update(float _DeltaTime);
	void Jump_Attack_End();
};

