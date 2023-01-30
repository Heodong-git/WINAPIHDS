#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Boss_Colonel : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_Colonel();
	~Boss_Colonel();

	// delete Function
	Boss_Colonel(const Boss_Colonel& _Other) = delete;
	Boss_Colonel(Boss_Colonel&& _Other) noexcept = delete;
	Boss_Colonel& operator=(const Boss_Colonel& _Other) = delete;
	Boss_Colonel& operator=(Boss_Colonel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	static float Time;
	float4 m_Dir;
	GameEngineRender* m_Render = nullptr;
};

