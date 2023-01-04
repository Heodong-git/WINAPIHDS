#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class EndTitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	EndTitleLevel();
	~EndTitleLevel();

	// delete Function
	EndTitleLevel(const EndTitleLevel& _Other) = delete;
	EndTitleLevel(EndTitleLevel&& _Other) noexcept = delete;
	EndTitleLevel& operator=(const EndTitleLevel& _Other) = delete;
	EndTitleLevel& operator=(EndTitleLevel&& _Other) noexcept = delete;

protected:

private:

};

