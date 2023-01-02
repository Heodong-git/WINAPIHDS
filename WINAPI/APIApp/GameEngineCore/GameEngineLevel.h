#pragma once

// 설명 : 게임안의 화면, 타이틀 화면, 엔딩화면, 맵에디터 화면 등을 Level 이라고 한다. 
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

