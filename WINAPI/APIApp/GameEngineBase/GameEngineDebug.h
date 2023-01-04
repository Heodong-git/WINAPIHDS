#pragma once
#include <assert.h>

// ���� : ������ ����׿� ���õ� �κе��� ��� �� Ŭ�������� �ذ��Ѵ�. 
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

	// static �Լ��� Ư¡ : this�� �������� �ʱ� ������ ��������� ����� �� ����.
	// ��ü ���� �ش� �Լ��� ȣ�� �� �� �ִ�. 
	static void LeakCheck();

protected:

private:

};

// �Է��� ���ڿ��� â�� ����ְ� assert(false) 
#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);