#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

enum class PlayerState
{
	IDLE,
	MOVE,
	JUMP,
	FALL,
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
	static float Time;
	float	     MoveSpeed = 400.0f;
	// �⺻ ���� - ������, ���ڿ��� ����
	std::string  DirString = "Right_";
	float4		 MoveDir = float4::Zero;
	// �÷��̾��� �⺻���´� ���̵�� �ʱ�ȭ
	PlayerState  StateValue = PlayerState::MOVE;
	GameEngineRender* AnimationRender = nullptr;
	bool		 Gravity = true;
	bool		 Jump = false;
	float		 JumpPower = 5.f;
	float4		PrevPos = float4::Zero;
	

	// ����üũ
	void DirCheck(const std::string_view& _AnimationName);

	// ����ü����
	void ChangeState(PlayerState _State);
	// ���� ������Ʈ 
	void UpdateState(float _DeltaTime);

	void Movecalculation(float _DeltaTime);

	// ��� ���°� ���� �����������غ���. 
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
	
	void DashStart();
	void DashUpdate(float _DeltaTime);
	void DashEnd();

};

