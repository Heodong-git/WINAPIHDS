#pragma once
#include <windows.h>
#include <assert.h>
#include <string>

class GameEngineDebug
{
public:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;
	
	static void LeakCheck();

protected:

private:

};

// 입력한 문자열을 창에 띄워주고 assert(false) 
#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);

// 게임엔진디버그라는 클래스를 만든 이유
// 디버깅을 위해 사용하는 함수나 기능들을 이 클래스에 모아두고 편리하게 사용하기 위해서. 