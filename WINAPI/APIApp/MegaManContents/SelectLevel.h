#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Title Level 에서 Game Start 를 선택했다면
// 해당 Level 로 넘어와서 캐릭터를 선택하는 Level 
class SelectLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SelectLevel();
	~SelectLevel();

	// delete Function
	SelectLevel(const SelectLevel& _Other) = delete;
	SelectLevel(SelectLevel&& _Other) noexcept = delete;
	SelectLevel& operator=(const SelectLevel& _Other) = delete;
	SelectLevel& operator=(SelectLevel&& _Other) noexcept = delete;

	bool SelectX = false;
	bool SelectZero = false;

protected:
	virtual void Loading() override;
	virtual void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}

	// 음.. 캐릭터가 선택되었다는걸 어떤식으로 표현해야할까. 
private:
};

