#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

enum class PlayerState
{
	NONE,
	RECALL,
	IDLE,
	MOVE,
	JUMP,
	JUMPATTACK,
	DOUBLEJUMP,
	FALL,
	SIT,
	SITATTACK,
	NOMALATTACK,
	DASH,
	DASHATTACK,
	HIT,
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
	float		 m_DashEffectLiveTime = 0.0f;
	float		 m_DashEffectMaxTime = 0.64f;
	// �̵��ӵ� 
	float	     m_MoveSpeed = 800.0f;
	// �⺻ ���� - ������, ���ڿ��� ����
	std::string  m_DirString = "Right_";
	// ���� 
	float4		 m_MoveDir = float4::Zero;

	// �÷��̾��� �⺻���´� ���̵�� �ʱ�ȭ
	PlayerState  m_StateValue = PlayerState::NONE;
	PlayerState  m_PrevState = PlayerState::NONE;
	PlayerState  m_NextState = PlayerState::NONE;

	// ������ 
	GameEngineRender* m_AnimationRender = nullptr;
	GameEngineRender* m_EffectRender = nullptr;

	// �浹ü 
	GameEngineCollision* m_Collision = nullptr;
	
	// �߷»��� 
	bool		 m_Gravity = true;
	bool		 m_Ground = true;
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

	// �ӽ� �Ϸ� 
	void NormalAttackStart();
	void NormalAttackUpdate(float _DeltaTime);
	void NormalAttackEnd();

	// �ӽ� �Ϸ�
	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();
	
	// �ӽ� �Ϸ� 
	void JumpAttackStart();
	void JumpAttackUpdate(float _DeltaTime);
	void JumpAttackEnd();

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

