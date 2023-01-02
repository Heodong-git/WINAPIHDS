#pragma once
#include <string>

// window ��ɻ��
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>


// ���� : ������â�� ���������ִ� Ŭ����
class GameEngineWindow
{
public:

	// ��ü���� �ش� �Լ��� ȣ���� �� �ְ� �����ϱ� ���ؼ� static ���� ����
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName);

	// ������ ũ�⼳��
	static void WindowSize(float4 _Size);
	
	// â ������ ��ǥ����
	static void WindowPos(float4 _Pos);

	// ������ ���ѷ���
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
	static HWND hWnd;				// �������ڵ鰪 
};

