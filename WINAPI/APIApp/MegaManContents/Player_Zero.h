#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

enum class PlayerState
{
	IDLE,
	MOVE,
	JUMP,
	DASH,
	NOMALATTACK,
	JUMPATTACK,
	DASHATTACK,
};

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
	static float Time;
	float	     MoveSpeed = 300.0f;

	// �⺻ ���� - ������, ���ڿ��� ����
	std::string Dir = "Right_";
	// �÷��̾��� �⺻���´� ���̵�� �ʱ�ȭ
	PlayerState StateValue = PlayerState::MOVE;
	GameEngineRender* AnimationRender = nullptr;

	// ����üũ
	void DirCheck();

	// ����ü����
	void ChangeState(PlayerState _State);
	// ���� ������Ʈ 
	void UpdateState(float _Time);

	// ��� ���°� ���� �����������غ���. 
	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	void NormalAttackStart();
	void NormalAttackUpdate(float _Time);
	void NormalAttackEnd();

	void JumpStart();
	void JumpUpdate(float _Time);
	void JumpEnd();

	void JumpAttackStart();
	void JumpAttackUpdate(float _Time);
	void JumpAttackEnd();
	
	void DashStart();
	void DashUpdate(float _Time);
	void DashEnd();
	
	void DashAttackStart();
	void DashAttackUpdate(float _Time);
	void DashAttackEnd();
};

