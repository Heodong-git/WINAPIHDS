#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineImage;
class GameEngineWindow
{
	static LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

public:
	// ������ �����Լ� 
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);
	
	// â��ũ��, ��ǥ����
	static void SettingWindowSize(float4 _Size);
	static void SettingWindowPos(float4 _Pos);

	// ��ũ�������� ��ȯ
	static float4 GetScreenSize()
	{
		return ScreenSize;
	}

	// ������ �ڵ鰪 ��ȯ 
	static HWND GetHWnd()
	{
		return HWnd;
	}

	// ������DC ��ȯ 
	static HDC GetWindowBackBufferHdc()
	{
		return WindowBackBufferHdc;
	}

	// ������� �̹��� ��ȯ 
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
	// ������ ���ѷ��� ( Ŭ���̾�Ʈ â�� �������� �ʰ� ����ؼ� ����ǵ��� )
	// �Լ��������� ���ڸ� �޾��ִ� ������ �Ѱ����� ������ �ƴ� 
	// �ٸ� ���α׷��� ������ �ۼ��� �Լ��� �־��ֱ⸸ �ϸ� ��������� �� �ֵ��� �ϱ� �����̴�.
	// ��, WindowLoop �� ������ ���ϴ� ���α׷��� ������ �ۼ��Ͽ� �־��ֱ⸸ �ϸ� ���ุ ����. 
	// callback ��� 
	static int WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)());

	GameEngineWindow();
	~GameEngineWindow();

	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

protected:

private:
	static float4 WindowSize;					// ���� �����Ǵ� �������� ũ�� ( �޴��� ���� ���Ե� ũ�� ) 
	static float4 ScreenSize;					// �����ϰ��� �ϴ� �������� ũ��
	static float4 WindowPos;					// ������â�� ������ �»�� ��ǥ 
	static HWND HWnd;							// ������ �ڵ鰪
	static HDC WindowBackBufferHdc;				// HDC : �����쿡 �׸��� �׸��� �ְ� ���ִ� ����
	static GameEngineImage* BackBufferImage;    // ȭ�鿡 �������� �̹��� ������
	static GameEngineImage* DoubleBufferImage;	// ���⿡ ��� �̹����� �׷�����, �Ŀ� �Լ��� Ȱ���Ͽ� �׷��� �̹����� BackBuffer�� �׷�����.
	static bool IsWindowUpdate;
};
