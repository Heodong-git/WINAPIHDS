#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	static float Time;
	float4 m_Dir;
	GameEngineRender* m_Render = nullptr;
	GameEngineCollision* m_Collision = nullptr;

};
