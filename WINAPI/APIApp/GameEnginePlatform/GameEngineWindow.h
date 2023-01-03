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
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);

	// 윈도우 크기설정
	static void SettingWindowSize(float4 _Size);
	
	// 창 생성시 좌표설정
	static void SettingWindowPos(float4 _Pos);

	static HWND GetHWnd()
	{
		return HWnd;
	}

	static HDC GetDrawHdc()
	{
		return DrawHdc;
	}

	// 윈도우 무한루프 ( 클라이언트 창을 종료하지 않고 계속해서 실행되도록 )
	// 함수포인터의 인자를 받아주는 이유는 한가지의 종류가 아닌 
	// 다른 프로그램의 로직이 작성된 함수를 넣어주기만 하면 실행시켜줄 수 있도록 하기 위함이다.
	// 즉, WindowLoop 는 실행을 원하는 프로그램의 로직을 작성하여 넣어주기만 하면
	// 실행만 해주는 녀석일 뿐.
	static int WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)());

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
	static float4 WindowSize;       // 실제 생성되는 윈도우의 크기 ( 메뉴바 등이 포함된 크기 ) 
	static float4 ScreenSize;		// 생성하고자 하는 윈도우의 크기
	static float4 WindowPos;		// 윈도우창을 생성할 좌상단 좌표 
	static HWND HWnd;				// 윈도우 핸들값
	static HDC DrawHdc;			    // HDC : 윈도우에 그림을 그릴수 있게 해주는 권한
};

