#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Monster_MetalT : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster_MetalT();
	~Monster_MetalT();

	// delete Function
	Monster_MetalT(const Monster_MetalT& _Other) = delete;
	Monster_MetalT(Monster_MetalT&& _Other) noexcept = delete;
	Monster_MetalT& operator=(const Monster_MetalT& _Other) = delete;
	Monster_MetalT& operator=(Monster_MetalT&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	static float Time;
	float4 Dir;
};

