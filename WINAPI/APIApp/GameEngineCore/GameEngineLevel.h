#pragma once

// ���� : ���Ӿ��� ȭ��, Ÿ��Ʋ ȭ��, ����ȭ��, �ʿ����� ȭ�� ���� Level �̶�� �Ѵ�. 
class GameEngineLevel
{
public:
	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:

private:

};

