#pragma once
#include <windows.h>
#include <assert.h>
#include <string>

// ���ӿ�������׶�� Ŭ������ ���� ����
// ������� ���� ����ϴ� �Լ��� ��ɵ��� ��Ƶΰ� ����ϱ� ����.
// ����׿� �ʿ��� �Լ����� ����� �� �ֵ��� �� Ŭ������ ���ս��ѵд�. 

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
	static void LeakPointBreak(int _Point);

protected:

private:

};

// �Է��� ���ڿ��� â�� ����ְ� assert(false) 
#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);