#pragma once
#include <Windows.h>
#include <assert.h>

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

	// static 함수의 특징 : this가 존재하지 않기 때문에 멤버변수를 사용할 수 없다.
	// 객체 없이 해당 함수를 호출 할 수 있다. 
	static void LeakCheck();

protected:

private:

};

//#define MessageBoxAssert(MsgText) MessageBoxA(nullptr, MsgText, "Error", MB_OK);	assert(false);