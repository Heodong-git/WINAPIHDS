#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class GameEngineRender;
class GameEngineCollision;
class Object_Door : public GameEngineActor
{
public:
	// constrcuter destructer
	Object_Door();
	~Object_Door();

	// delete Function
	Object_Door(const Object_Door& _Other) = delete;
	Object_Door(Object_Door&& _Other) noexcept = delete;
	Object_Door& operator=(const Object_Door& _Other) = delete;
	Object_Door& operator=(Object_Door&& _Other) noexcept = delete;

	inline GameEngineCollision* GetCollider()
	{
		return m_Collider;
	}

	inline bool IsCollision()
	{
		return m_IsCollision;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
	
private:
	GameEngineRender* m_AnimationRender = nullptr;
	GameEngineCollision* m_Collider = nullptr;
	GameEngineSoundPlayer m_Sound;

	bool			    m_Open = false;
	bool				m_IsCollision = false;
};
