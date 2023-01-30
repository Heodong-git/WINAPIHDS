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
	DASH,
	NOMALATTACK,
	JUMPATTACK,
	DASHATTACK,
};

// 디버깅용 키 다시 만들어야함. 
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
	// 기본 방향 - 오른쪽, 문자열로 저장
	std::string  m_DirString = "Right_";
	float4		 m_MoveDir = float4::Zero;
	// 플레이어의 기본상태는 아이들로 초기화
	PlayerState  m_StateValue = PlayerState::MOVE;
	GameEngineRender* m_AnimationRender = nullptr;
	bool		 m_Gravity = true;
	bool		 m_Jump = false;
	float		 m_JumpPower = 5.f;
	float4		 m_PrevPos = float4::Zero;
	
	// 디버그용
	inline void DebugSwitch()
	{
		m_DebugMode = !m_DebugMode;
	}

	// 방향체크
	void DirCheck(const std::string_view& _AnimationName);

	// 상태체인지
	void ChangeState(PlayerState _State);
	// 상태 업데이트 
	void UpdateState(float _DeltaTime);

	void Movecalculation(float _DeltaTime);

	// 임시 완료 
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
	
	void DashStart();
	void DashUpdate(float _DeltaTime);
	void DashEnd();

};

