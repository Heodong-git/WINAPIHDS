#pragma once

// 설명 : 윈도우창을 생성시켜주는 클래스
class GameEngineWindow
{
public:

	// 객체없이 해당 함수를 호출할 수 있게 설계하기 위해서 static 으로 선언
	static void WindowCreate();

	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

protected:

private:

};

