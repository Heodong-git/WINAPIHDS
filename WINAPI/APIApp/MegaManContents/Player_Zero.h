#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

enum class STATEVALUE
{
	NONE,		 // 초기화
	RECALL,		 // 리콜 (리스폰)
	IDLE,		 // 아이들 
	MOVE,		 // 이동
	JUMP,		 // 점프
	FALL,	     // 낙하
	FALL_END,	 // 낙하종료
	ATTACK_FIRST,		 // 공격
	ATTACK_SECOND,
	ATTACK_THIRD,
	DASH,		 // 대쉬 
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

	void SetStartPos(float4 _Pos)
	{
		m_StartPos = _Pos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::string ColMapName;

	// 디버그용 변수
	bool		 m_DebugMode = false;

	// 플레이어가 사용하는 변수
	float	     m_MoveSpeed = 500.0f;
	bool		 m_Jump = false;
	bool	     m_Falling = false;  
	float		 m_MaxJumpTime = 1.5f;
	float		 m_JumpPower = 0.0f;
	float	     m_GravityPower = 200.0f;
	bool		 IsJumpMax = false;

	float4	     m_StartPos = float4::Zero;

	std::string  m_DirString = "Right_";
	float4		 m_MoveDir = float4::Zero;
	COLORREF	 m_GroundCollisionPixel = RGB(57, 255, 20);

	// 플레이어의 기본상태는 아이들로 초기화
	STATEVALUE  m_StateValue = STATEVALUE::NONE;
	STATEVALUE  m_PrevState = STATEVALUE::NONE;
	STATEVALUE  m_NextState = STATEVALUE::NONE;
 
	GameEngineRender* m_AnimationRender = nullptr;
	GameEngineCollision* m_Collider = nullptr;
	GameEngineCollision* m_SaberCollider = nullptr;
	
	// 디버그용
	inline void DebugSwitch()
	{
		m_DebugMode = !m_DebugMode;
	}
	void DebugMove(float _DeltaTime);

	// 방향체크 + 애니메이션 렌더 
	void AnimDirCheck(const std::string_view& _AnimationName);
	bool NextMoveCheck(float _DeltaTime);
	void ChangeState(STATEVALUE _State);
	void GroundCollisionCheck(float4 _Pos = float4::Zero);

	void Gravity(float _DeltaTime);

	void PlayerCreateAnimation();

	int GetColor(float4 Pos = float4::Zero);

	bool IsGround(float4 Pos = float4::Zero);

	// 상태 업데이트 
	void UpdateState(float _DeltaTime);
	
	// 상태
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

