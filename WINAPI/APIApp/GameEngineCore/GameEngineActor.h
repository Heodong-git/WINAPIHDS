#pragma once

// 설명 : 게임내부에서 움직이는 물체들 , Level 에 속해있으며 타이틀이미지, 계속하기 버튼 등을 말한다. 
class GameEngineActor
{
public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

protected:

private:

};

