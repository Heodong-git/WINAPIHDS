#pragma once

// ���� : ������â�� ���������ִ� Ŭ����
class GameEngineWindow
{
public:

	// ��ü���� �ش� �Լ��� ȣ���� �� �ְ� �����ϱ� ���ؼ� static ���� ����
	static void WindowCreate();

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

};

