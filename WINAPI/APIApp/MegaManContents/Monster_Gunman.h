#pragma once
#include <GameEngineCore/GameEngineActor.h>


enum class GunmanState
{
	IDLE,
	SHOT,
};

class GameEngineCollision;
class Monster_GunMan : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster_GunMan();
	~Monster_GunMan();

	// delete Function
	Monster_GunMan(const Monster_GunMan& _Other) = delete;
	Monster_GunMan(Monster_GunMan&& _Other) noexcept = delete;
	Monster_GunMan& operator=(const Monster_GunMan& _Other) = delete;
	Monster_GunMan& operator=(Monster_GunMan&& _Other) noexcept = delete;

	inline const std::string& GetDirString() const
	{
		return m_DirString;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	static float Time;
	std::string  m_DirString = "Left_";
	GameEngineRender* m_AnimationRender = nullptr;
	GameEngineCollision* m_Collider = nullptr;

	float	    m_ShotRange = 800.0f;
	float	    m_ShotCooldown = 0.0f;
	float		m_ShotMaxCooldown = 2.5f;
	
	GunmanState m_PrevState = GunmanState::IDLE;
	GunmanState m_CurState = GunmanState::IDLE;
	GunmanState m_NextState = GunmanState::IDLE;
	
	void AnimDirCheck(const std::string_view& _AnimationName);

	void ChangeState(GunmanState _State);
	void UpdateState(float _DeltaTime);

	void Idle_Start();
	void Idle_Update(float _DeltaTime);
	void Idle_End();

	void Shot_Start();
	void Shot_Update(float _DeltaTime);
	void Shot_End();
};

