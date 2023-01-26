#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Title Level ���� Game Start �� �����ߴٸ�
// �ش� Level �� �Ѿ�ͼ� ĳ���͸� �����ϴ� Level 
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
	virtual void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}

private:
	bool m_ChangeLevel = false;
	float m_ChangeTime = 0.0f;
};

