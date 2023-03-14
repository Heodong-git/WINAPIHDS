#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineImage;
class GameEngineWindow
{
	static LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

public:
	// 윈도우 생성함수 
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);
	
	// 창의크기, 좌표설정
	static void SettingWindowSize(float4 _Size);
	static void SettingWindowPos(float4 _Pos);

	// 스크린사이즈 반환
	static float4 GetScreenSize()
	{
		return ScreenSize;
	}

	// 윈도우 핸들값 반환 
	static HWND GetHWnd()
	{
		return HWnd;
	}

	// 윈도우DC 반환 
	static HDC GetWindowBackBufferHdc()
	{
		return WindowBackBufferHdc;
	}

	// 더블버퍼 이미지 반환 
	static GameEngineImage* GetDoubleBufferImage()
	{
		return DoubleBufferImage;
	}

	static void AppOff()
	{
		IsWindowUpdate = false;
	}

	static void DoubleBufferClear();
	static void DoubleBufferRender();
	// 윈도우 무한루프 ( 클라이언트 창을 종료하지 않고 계속해서 실행되도록 )
	// 함수포인터의 인자를 받아주는 이유는 한가지의 종류가 아닌 
	// 다른 프로그램의 로직이 작성된 함수를 넣어주기만 하면 실행시켜줄 수 있도록 하기 위함이다.
	// 즉, WindowLoop 는 실행을 원하는 프로그램의 로직을 작성하여 넣어주기만 하면 실행만 해줌. 
	// callback 기반 
	static int WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)());

	static float4 GetMousePosition();

	GameEngineWindow();
	~GameEngineWindow();

	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

protected:

private:
	static float4 WindowSize;					// 실제 생성되는 윈도우의 크기 ( 메뉴바 등이 포함된 크기 ) 
	static float4 ScreenSize;					// 생성하고자 하는 윈도우의 크기
	static float4 WindowPos;					// 윈도우창을 생성할 좌상단 좌표 
	static HWND HWnd;							// 윈도우 핸들값
	static HDC WindowBackBufferHdc;				// HDC : 윈도우에 그림을 그릴수 있게 해주는 권한
	static GameEngineImage* BackBufferImage;    // 화면에 보여지는 이미지 최종본
	static GameEngineImage* DoubleBufferImage;	// 여기에 모든 이미지를 그려내고, 후에 함수를 활용하여 그려진 이미지를 BackBuffer에 그려낸다.
	static bool IsWindowUpdate;
};

// 윈도우 창과 관련된 기능들을 이 클래스에 모아서 사용하기 위해서 제작
// ex) 윈도우창 생성, 윈도우 창의 크기 변경, 메세지처리, 윈도우종료 등
// 윈도우 클래스 내부에 변수들을 모두 static 으로 작성한 이유는? 
// 윈도우 창은 하나만 만들어진다고 생각하고 작성했기 때문에 모두 static 으로 작성하고, 편하게 사용하기 위해서이다.
// 더블버퍼링을 해야하는 이유?
// 화면을 한번에 그려내고, 틱마다 그려진 화면을 가져와서 출력 하지 않고
// 바로바로 출력하게 되면 화면에 똥이 남게 된다. 
