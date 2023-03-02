#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineCollision;
// ���� :
class Ladder : public GameEngineActor
{
public:
	// constrcuter destructer
	Ladder();
	~Ladder();

	// delete Function
	Ladder(const Ladder& _Other) = delete;
	Ladder(Ladder&& _Other) noexcept = delete;
	Ladder& operator=(const Ladder& _Other) = delete;
	Ladder& operator=(Ladder&& _Other) noexcept = delete;

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
	void Render(float _DeltaTime) override;
	void Update(float _DeltaTime) override;

private:
	GameEngineCollision* m_Collider = nullptr;
	bool			     m_IsCollision = false;
};
