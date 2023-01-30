#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

enum class PlayerState
{
	RECALL,
	IDLE,
	MOVE,
	JUMP,
	FALL,
	SIT,
	SITATTACK,
	DASH,
	NOMALATTACK,
	JUMPATTACK,
	DASHATTACK,
};

// ������ Ű �ٽ� ��������. 
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
	bool		 m_DebugMode = false;
	static float m_Time;
	float	     m_MoveSpeed = 700.0f;
	// �⺻ ���� - ������, ���ڿ��� ����
	std::string  m_DirString = "Right_";
	float4		 m_MoveDir = float4::Zero;
	// �÷��̾��� �⺻���´� ���̵�� �ʱ�ȭ
	PlayerState  m_StateValue = PlayerState::RECALL;
	PlayerState  m_PrevState = PlayerState::RECALL;
	PlayerState  m_NextState = PlayerState::RECALL;
	GameEngineRender* m_AnimationRender = nullptr;
	bool		 m_Gravity = true;
	bool		 m_Jump = false;
	float		 m_JumpPower = 5.f;
	float4		 m_PrevPos = float4::Zero;
	
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

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void NormalAttackStart();
	void NormalAttackUpdate(float _DeltaTime);
	void NormalAttackEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();

	void FallStart();
	void FallUpdate(float _DeltaTime);
	void FallEnd();
	
	void SitStart();
	void SitUpdate(float _DeltaTime);
	void SitEnd();

	void SitAttackStart();
	void SitAttackUpdate(float _DeltaTime);
	void SitAttackEnd();
	
	void DashStart();
	void DashUpdate(float _DeltaTime);
	void DashEnd();

};

