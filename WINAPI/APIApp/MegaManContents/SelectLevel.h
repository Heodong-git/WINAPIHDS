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

protected:
	virtual void Loading() override;
	virtual void Update() override;

private:

};

