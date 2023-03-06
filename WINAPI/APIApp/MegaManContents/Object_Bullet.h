#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Object_Bullet : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Bullet();
	~Object_Bullet();

	// delete Function
	Object_Bullet(const Object_Bullet& _Other) = delete;
	Object_Bullet(Object_Bullet&& _Other) noexcept = delete;
	Object_Bullet& operator=(const Object_Bullet& _Other) = delete;
	Object_Bullet& operator=(Object_Bullet&& _Other) noexcept = delete;
	
	inline void SetMoveDir(const float4 _Dir)
	{
		m_MoveDir = _Dir;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* m_AnimationRender = nullptr;
	GameEngineCollision* m_Collider = nullptr;

	float4				m_MoveDir = float4::Left;
	float				m_MoveSpeed = 700.0f;
	bool				m_IsCollision = false;
	float			    m_LiveTime = 2.0f;
	int				    m_Damage = 1;
};
