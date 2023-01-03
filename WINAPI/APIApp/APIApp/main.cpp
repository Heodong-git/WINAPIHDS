#include <Windows.h>
// ����
// ���� ���� ���͸��� ��� + ..\ �� �����Ǿ� �ֱ� ������ 
// ���������� �ִ� ��� ���� / ������Ϸ� include �� ����
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>

void TestGameStart()
{
	int a = 0;
}

int x = 0;

void TestGameLoop()
{
	// ȭ�鿡 �׸��� �׷��ִ� �Լ��Դϴ�.

	++x;

	Rectangle(GameEngineWindow::GetDrawHdc(), 0 + x, 0, 100 + x, 100);

	// ���Ͱ� �����̰� �����
	// �÷��̾ �����̰� ������ �Ѵ�.
	int a = 0;
}

void TestGameEnd()
{
	int a = 0;
}


// �Ӽ� : �����ý��� -> â���� �ٲ��ָ� ������� WinMain ���� �������Լ� ����
// ����������(�����Ķ����) , OS�� ���ڸ� ä���ְ� �ȴ�.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)

{
	// ��üũ
	GameEngineDebug::LeakCheck();

	// ������ ����
	GameEngineWindow::WindowCreate(hInstance, "MainWindow", {1360, 768}, { 0, 0});
	
	// ���α׷� ����, ���ѷ���
	GameEngineWindow::WindowLoop(TestGameStart,TestGameLoop,TestGameEnd);

	return 0;
}



// 20230102
// 1. ���Ե��͸� ..\ �� ���� [�Ϸ�]
// 2. GameEngineWindow , Math �ڵ��ۼ� [�Ϸ�]
// 3. ���� <

// 20230103
// 1. Math , Window


