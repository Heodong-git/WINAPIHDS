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

private:

};

