#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineCollision;
// Ό³Έν :
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

protected:
	void Start() override;
	void Render(float _DeltaTime) override;

private:
	GameEngineCollision* m_Collider = nullptr;
	
};
