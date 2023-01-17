#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Select Level 에서 캐릭터를 선택했다면
// 진입하여 본격적으로 게임을 진행하는 Level 
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
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:

};

