#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 타이틀화면
// 게임시작, 옵션, 종료 등을 선택할 수 있는 Level 
class UI_TitleUI;
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	virtual void Loading() override;
	virtual void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}

private:
	UI_TitleUI* m_TitleUI = nullptr;
};

