#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Select Level ���� ĳ���͸� �����ߴٸ�
// �����Ͽ� ���������� ������ �����ϴ� Level 
class SigmaStageLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SigmaStageLevel();
	~SigmaStageLevel();

	// delete Function
	SigmaStageLevel(const SigmaStageLevel& _Other) = delete;
	SigmaStageLevel(SigmaStageLevel&& _Other) noexcept = delete;
	SigmaStageLevel& operator=(const SigmaStageLevel& _Other) = delete;
	SigmaStageLevel& operator=(SigmaStageLevel&& _Other) noexcept = delete;

protected:
	virtual void Loading() override;
	virtual void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}

private:

};

