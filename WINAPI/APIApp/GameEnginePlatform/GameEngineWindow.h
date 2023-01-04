#pragma once
#include <string>

// window ��ɻ��
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

// ���� : ���α׷��� ���۽�ų ������â�� �����ϴ� Ŭ���� 
class GameEngineWindow
{
public:
	// ��ü���� �ش� �Լ��� ȣ���� �� �ְ� �����ϱ� ���ؼ� static ���� ����
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);

	// ������ ũ�⼳��
	static void SettingWindowSize(float4 _Size);
	
	// â ������ ��ǥ����
	static void SettingWindowPos(float4 _Pos);

	static HWND GetHWnd()
	{
		return HWnd;
	}

	static HDC GetDrawHdc()
	{
		return DrawHdc;
	}

	// ������ ���ѷ��� ( Ŭ���̾�Ʈ â�� �������� �ʰ� ����ؼ� ����ǵ��� )
	// �Լ��������� ���ڸ� �޾��ִ� ������ �Ѱ����� ������ �ƴ� 
	// �ٸ� ���α׷��� ������ �ۼ��� �Լ��� �־��ֱ⸸ �ϸ� ��������� �� �ֵ��� �ϱ� �����̴�.
	// ��, WindowLoop �� ������ ���ϴ� ���α׷��� ������ �ۼ��Ͽ� �־��ֱ⸸ �ϸ�
	// ���ุ ���ִ� �༮�� ��.
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
	static float4 WindowSize;       // ���� �����Ǵ� �������� ũ�� ( �޴��� ���� ���Ե� ũ�� ) 
	static float4 ScreenSize;		// �����ϰ��� �ϴ� �������� ũ��
	static float4 WindowPos;		// ������â�� ������ �»�� ��ǥ 
	static HWND HWnd;				// ������ �ڵ鰪
	static HDC DrawHdc;			    // HDC : �����쿡 �׸��� �׸��� �ְ� ���ִ� ����
};



// 1. GameEngineWindow Ŭ�������� ������ �����Ű�� ���� ������â�� �����ϰ�
// ������â���� �ʿ��� ���۵��� �����Ѵ�. ex) ȭ�鿡 �׸���, â��ũ�� ���� �̵� �� 