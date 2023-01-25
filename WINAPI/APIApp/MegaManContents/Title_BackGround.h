#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Title_BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	Title_BackGround();
	~Title_BackGround();

	// delete Function
	Title_BackGround(const Title_BackGround& _Other) = delete;
	Title_BackGround(Title_BackGround&& _Other) noexcept = delete;
	Title_BackGround& operator=(const Title_BackGround& _Other) = delete;
	Title_BackGround& operator=(Title_BackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* m_Render = nullptr;
};

