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
	float	     MoveSpeed = 800.0f;

	// 기본 방향 - 오른쪽, 문자열로 저장
	std::string DirString = "Right_";
	// 플레이어의 기본상태는 아이들로 초기화
	PlayerState StateValue = PlayerState::MOVE;
	GameEngineRender* AnimationRender = nullptr;

	// 방향체크
	void DirCheck(const std::string_view& _AnimationName);

	// 상태체인지
	void ChangeState(PlayerState _State);
	// 상태 업데이트 
	void UpdateState(float _Time);

	// 어떠한 상태가 있을 것인지생각해본다. 
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

