#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

enum class PlayerState
{
	NONE,			 // �ʱ�ȭ
	RECALL,			 // ����
	IDLE,			 // ���̵�
	MOVE,			 // ����
	JUMP,		     // ����
	JUMP_ATTACK,		 // ��������
	RIDEUP,			 // ��ٸ�Ÿ�� 
	RIDEUP_ATTACK,
	WALL,
	WALL_ATTACK,
	DOUBLEJUMP,	     // �̴������ε� �������� �Ƹ���?
	FALL,			 // ����
	SIT,			 // �ɱ�
	SITATTACK,		 // �ɱ����
	ATTACK_FIRST,	 // ���� 1Ÿ
	ATTACK_SECOND,	 // 2Ÿ
	ATTACK_THIRD,    // 3Ÿ
	DASH,			 // �뽬
	DASH_ATTACK,		 // �뽬���� 
	HIT,			 // ��Ʈ
	
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
	// ��� ����Ű�����.. �����?��������
	static float m_Time;
	float		 m_HitTime = 0.5f;
	// �̵��ӵ� 
	float	     m_MoveSpeed = 1000.0f;
	bool		 m_Jump = false;
	float		 m_JumpHeight = 0.0f;
	float	     m_JumpTime = 1.0f;   // �ӽ� 
	float		 m_JumpPower = -650.0f;
	float	     m_GravityPower = 300.0f; // Gravity

	bool		 m_Ground = false;
	bool		 m_Gravity = true;
	std::string  m_DirString = "Right_";
	float4		 m_MoveDir = float4::Zero;

	// �÷��̾��� �⺻���´� ���̵�� �ʱ�ȭ
	PlayerState  m_StateValue = PlayerState::NONE;
	PlayerState  m_PrevState = PlayerState::NONE;
	PlayerState  m_NextState = PlayerState::NONE;
 
	GameEngineRender* m_AnimationRender = nullptr;
	GameEngineCollision* m_Collision = nullptr;
	
	
	// ����׿�
	inline void DebugSwitch()
	{
		m_DebugMode = !m_DebugMode;
	}

	// ����üũ
	void DirCheck(const std::string_view& _AnimationName);

	// ����ü����
	void ChangeState(PlayerState _State);
	// ���� ������Ʈ 
	void UpdateState(float _DeltaTime);

	void Movecalculation(float _DeltaTime);

	// �ӽ� �Ϸ� 
	void RecallStart();
	void RecallUpdate(float _DeltaTime);
	void RecallEnd();

	// �ӽ� �Ϸ�
	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	// �ӽ� �Ϸ� 
	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void Attack_First_Start();
	void Attack_First_Update(float _DeltaTime);
	void Attack_First_End();

	void Attack_Second_Start();
	void Attack_Second_Update(float _DeltaTime);
	void Attack_Second_End();

	void Attack_Third_Start();
	void Attack_Third_Update(float _DeltaTime);
	void Attack_Third_End();


	// �ӽ� �Ϸ�
	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();
	
	// �ӽ� �Ϸ� 
	void JumpAttackStart();
	void JumpAttackUpdate(float _DeltaTime);
	void JumpAttackEnd();
	
	void RideUpStart();
	void RideUpUpdate(float _DeltaTime);
	void RideUpEnd();

	void RideUpAttackStart();
	void RideUpAttackUpdate(float _DeltaTime);
	void RideUpAttackEnd();

	void WallStart();
	void WallUpdate(float _DeltaTime);
	void WallEnd();

	void WallAttackStart();
	void WallAttackUpdate(float _DeltaTime);
	void WallAttackEnd();

	// �ӽ� �Ϸ�
	void DoubleJumpStart();
	void DoubleJumpUpdate(float _DeltaTime);
	void DoubleJumpEnd();

	// ��� ����
	void FallStart();
	void FallUpdate(float _DeltaTime);
	void FallEnd();
	
	// �ӽ� �Ϸ�
	void SitStart();
	void SitUpdate(float _DeltaTime);
	void SitEnd();

	// �ӽ� �Ϸ�
	void SitAttackStart();
	void SitAttackUpdate(float _DeltaTime);
	void SitAttackEnd();
	
	// �ӽ� �Ϸ� 
	void DashStart();
	void DashUpdate(float _DeltaTime);
	void DashEnd();

	// ������
	void HitStart();
	void HitUpdate(float _DeltaTime);
	void HitEnd();

};

