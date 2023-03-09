#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>
#include <string>

// 보스방입장하고나서부터 카메라, 플레이어 어떻게 움직일지부터 내일 다시. 

enum class STATEVALUE
{
	NONE,		         // 기본
	RECALL,		         // 리콜 (리스폰)
	IDLE,		         // 아이들 
	MOVE,		         // 이동
	JUMP,		         // 점프
	FALL,	             // 낙하
	ATTACK_FIRST,		 // 공격
	ATTACK_SECOND,
	ATTACK_THIRD,
	DASH,		         // 대쉬 
	JUMP_ATTACK,		 // 점프공격
	RIGHT_WALL,		     // 벽타기
	RIGHT_WALL_JUMP,
	LEFT_WALL,
	LEFT_WALL_JUMP,
	RIDE_UP,
	DOOR_CONTACT,
	HIT,
	BIGHIT,
	STAGE_CLEAR
};

class GameEngineCollision;
class SpacePortLevel;
class UI_PlayerHpBar;
class Player_Zero : public GameEngineActor
{
	// 이럴꺼면 그냥 처음부터 Level에서 static 으로.. 받을걸 
	friend class SpacePortLevel;
	friend class Monster_GunMan;
	friend class Object_Bullet;
	friend class Object_Door;
	friend class Effect_Lightning;

public:
	// constrcuter destructer
	Player_Zero();
	~Player_Zero();

	// delete Function
	Player_Zero(const Player_Zero& _Other) = delete;
	Player_Zero(Player_Zero&& _Other) noexcept = delete;
	Player_Zero& operator=(const Player_Zero& _Other) = delete;
	Player_Zero& operator=(Player_Zero&& _Other) noexcept = delete;

	inline void SetStartPos(float4 _Pos)
	{
		m_StartPos = _Pos;
	}

	// 이펙트클래스에서 출력시 방향을 받아와야함 
	inline const std::string& GetDirString() const
	{
		return m_DirString;
	}

	inline void Damage(int _Damage)
	{
		m_Hp -= _Damage;
	}

	inline void SetHpBar(UI_PlayerHpBar* _HpBar)
	{
		m_HpBar = _HpBar;
	}

	inline int GetHp() const
	{
		return m_Hp;
	}

	inline STATEVALUE GetState()
	{
		return m_PrevState;
	}

	inline void SetBossContact(bool _Value)
	{
		m_IsBossContact = true;
	}

	inline bool IsBossContact()
	{
		return m_IsBossContact;
	}

	inline float GetMoveSpeed()
	{
		return m_MoveSpeed;
	}

	inline void SetBossFight(bool _Value)
	{
		m_IsBossFight = _Value;
	}

	inline bool IsBossFight()
	{
		return m_IsBossFight;
	}

	GameEngineCollision* GetSaberCollider() const
	{
		return m_SaberCollider;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	std::string ColMapName = "ColMap_SpacePort.bmp";
	// 디버그용 변수
	bool		 m_DebugMode = false;
	// ---------------------------------
	float	     m_MoveSpeed = 550.0f;
	bool		 m_IsJump = false;  
	float		 m_JumpPower = 0.0f;
	float		 m_JumpPowerMax = 750.0f;
	float	     m_GravityPower = 750.0f;
	float		 m_GravityMgf = 2.4f;
	bool		 m_IsJumpMax = false;
	float		 m_WallJumpPower = 700.0f;
	bool		 m_IsHit = false;
	float		 m_DoorCol_MoveSpeed = 100.0f;

	// 수치확인해서 초기화 
	float		 m_LeftMaxPosX = 17800.0f;
	float		 m_RightMaxPosX = 19050.0f;

	bool		 m_IsBossContact = false;
	bool		 m_IsBossFight = false;

	bool		 m_IsTiring = false;


	UI_PlayerHpBar* m_HpBar = nullptr;
	int			 m_Hp = 10;

	float        m_DashSpeed = 1000.0f;
	float4       m_DashDistance = float4{ 150.0f , 0.0f };
	float4	     m_StartPos = float4::Zero;

	std::string  m_DirString = "Right_";
	float4		 m_MoveDir = float4::Zero;
	COLORREF	 m_GroundPixel = RGB(255, 255, 255);
	COLORREF	 m_FallPixel = RGB(0, 0, 0);

	// 플레이어의 기본상태는 아이들로 초기화
	STATEVALUE  m_StateValue = STATEVALUE::NONE;
	STATEVALUE  m_PrevState = STATEVALUE::NONE;
	STATEVALUE  m_NextState = STATEVALUE::NONE;
 
	GameEngineRender* m_AnimationRender = nullptr;
	GameEngineCollision* m_Collider = nullptr;
	GameEngineCollision* m_SaberCollider = nullptr;
	float4				 m_SaberColliderScale = float4{ 250, 250 };

	SpacePortLevel* m_SpLevel = nullptr;

	float4 m_RightNormalAttackPos = float4{ 200, -75 };
	float4 m_LeftNormalAttackPos = float4{ -200, -75 };

	// 이게 맞나?ㅋㅋㅋㅋ 
	GameEngineSoundPlayer m_AttackSound;
	GameEngineSoundPlayer m_SaberSound;
	GameEngineSoundPlayer m_DashSound;
	GameEngineSoundPlayer m_RecallSound;
	GameEngineSoundPlayer m_JumpSound;
	GameEngineSoundPlayer m_WallSound;
	GameEngineSoundPlayer m_LandingSound;
	GameEngineSoundPlayer m_ClearSound;
	GameEngineSoundPlayer m_ReadySound;
	GameEngineSoundPlayer m_HitSound;
	
	// 디버그용
	inline void DebugSwitch()
	{
		m_DebugMode = !m_DebugMode;
	}
	void DebugMove(float _DeltaTime);

	// 방향체크 + 애니메이션 렌더 
	void AnimDirCheck(const std::string_view& _AnimationName);
	void ChangeState(STATEVALUE _State);
	void GroundCollisionCheck(float4 _Pos = float4::Zero);


	// 중력
	void Gravity(float _DeltaTime);

	// 애니메이션 생성
	void PlayerCreateAnimation();

	// 충돌이미지의 픽셀컬러를 가져온다. 
	int GetColor(float4 Pos = float4::Zero);


	// --------------------------- 맵충돌픽셀체크 -------------------------
	// 땅에 박혔는지 체크 
	bool IsHitTheGround(float4 Pos = float4::Zero);
	bool IsHitTheRightWall(float4 Pos = float4::Zero);
	// 땅체크 
	bool IsGround(float4 Pos = float4::Zero);
	// 낙하체크
	bool IsFall(float4 Pos = float4::Zero);

	// 벽체크
	// 수정필요
	bool IsRightWall(float4 Pos = float4::Zero);
	bool IsLeftWall(float4 Pos = float4::Zero);
	bool IsTopWall(float4 Pos = float4::Zero);

	// --------------------------------------------------------------------

	// 왼쪽으로 못빠져나가게
	bool IsLeftOver();
	bool CameraPosCheck();

	// 보스방일 경우에 왼쪽 오른쪽을 전부 체크해야함
	bool IsBossRoomLeftOver();
	bool IsBossRoomRightOver();
	bool IsTiring()
	{
		return GetHp() <= 4;
	}

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

	void Right_Wall_Start();
	void Right_Wall_Update(float _DeltaTime);
	void Right_Wall_End();

	void Right_Wall_Jump_Start();
	void Right_Wall_Jump_Update(float _DeltaTime);
	void Right_Wall_Jump_End();

	void Left_Wall_Start();
	void Left_Wall_Update(float _DeltaTime);
	void Left_Wall_End();

	void Left_Wall_Jump_Start();
	void Left_Wall_Jump_Update(float _DeltaTime);
	void Left_Wall_Jump_End();

	void RideUp_Start();
	void RideUp_Update(float _DeltaTime);
	void RideUp_End();

	void Door_Contact_Start();
	void Door_Contact_Update(float _DeltaTime);
	void Door_Contact_End();

	void Hit_Start();
	void Hit_Update(float _DeltaTime);
	void Hit_End();

	void BigHit_Start();
	void BigHit_Update(float _DeltaTime);
	void BigHit_End();

	void StageClear_Start();
	void StageClear_Update(float _DeltaTime);
	void StageClear_End();
};

