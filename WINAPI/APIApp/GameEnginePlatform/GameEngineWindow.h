#pragma once
#include <string>

// window 기능사용
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>


// 설명 : 윈도우창을 생성시켜주는 클래스
class GameEngineWindow
{
public:

	// 객체없이 해당 함수를 호출할 수 있게 설계하기 위해서 static 으로 선언
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName);

	// 윈도우 크기설정
	static void WindowSize(float4 _Size);
	
	// 창 생성시 좌표설정
	static void WindowPos(float4 _Pos);

	// 윈도우 무한루프
	static int WindowLoop();

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
	static HWND hWnd;				// 윈도우핸들값 
};

