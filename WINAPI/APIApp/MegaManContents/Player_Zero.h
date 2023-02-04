#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

enum class PlayerState
{
	NONE,			 // 초기화
	RECALL,			 // 리콜
	IDLE,			 // 아이들
	MOVE,			 // 무브
	JUMP,		     // 점프
	JUMP_ATTACK,		 // 점프공격
	RIDEUP,			 // 사다리타기 
	RIDEUP_ATTACK,
	WALL,
	WALL_ATTACK,
	DOUBLEJUMP,	     // 이단점프인데 이제없음 아마도?
	FALL,			 // 낙하
	SIT,			 // 앉기
	SITATTACK,		 // 앉기공격
	ATTACK_FIRST,	 // 공격 1타
	ATTACK_SECOND,	 // 2타
	ATTACK_THIRD,    // 3타
	DASH,			 // 대쉬
	DASH_ATTACK,		 // 대쉬공격 
	HIT,			 // 히트
	
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
	// 디버그용 변수
	bool		 m_DebugMode = false;
	// 어디서 썼던거같은데.. 어디지?ㅋㅋㅋㅋ
	static float m_Time;
	float		 m_HitTime = 0.5f;
	float		 m_DashEffectLiveTime = 0.0f;
	float		 m_DashEffectMaxTime = 0.64f;
	// 이동속도 
	float	     m_MoveSpeed = 1000.0f;
	// 기본 방향 - 오른쪽, 문자열로 저장
	std::string  m_DirString = "Right_";
	// 방향 
	float4		 m_MoveDir = float4::Zero;

	// 플레이어의 기본상태는 아이들로 초기화
	PlayerState  m_StateValue = PlayerState::NONE;
	PlayerState  m_PrevState = PlayerState::NONE;
	PlayerState  m_NextState = PlayerState::NONE;

	// 렌더러 
	GameEngineRender* m_AnimationRender = nullptr;
	GameEngineRender* m_EffectRender = nullptr;

	// 충돌체 
	GameEngineCollision* m_Collision = nullptr;
	
	// 중력상태 
	bool		 m_Gravity = true;
	bool		 m_Ground = true;
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

	// 임시 완료
	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	// 임시 완료 
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


	// 임시 완료
	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();
	
	// 임시 완료 
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

	// 임시 완료
	void DoubleJumpStart();
	void DoubleJumpUpdate(float _DeltaTime);
	void DoubleJumpEnd();

	// 잠깐 보류
	void FallStart();
	void FallUpdate(float _DeltaTime);
	void FallEnd();
	
	// 임시 완료
	void SitStart();
	void SitUpdate(float _DeltaTime);
	void SitEnd();

	// 임시 완료
	void SitAttackStart();
	void SitAttackUpdate(float _DeltaTime);
	void SitAttackEnd();
	
	// 임시 완료 
	void DashStart();
	void DashUpdate(float _DeltaTime);
	void DashEnd();

	// 진행중
	void HitStart();
	void HitUpdate(float _DeltaTime);
	void HitEnd();

};

