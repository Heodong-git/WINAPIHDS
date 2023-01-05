#pragma once
#include <windows.h>
#include <assert.h>
#include <string>

// 설명 : 게임의 디버그와 관련된 부분들을 모두 이 클래스에서 해결한다. 
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