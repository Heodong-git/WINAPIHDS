#include <Windows.h>
// ������ ������ ���ؼ� ��� ������Ʈ���� ������ �ִ��� �� �� �ְ� �ۼ�
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>


// �Ӽ� : ���������� -> â���� �ٲ��ָ� ������� WinMain ���� �������Լ� ����
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)

{
	// ��üũ
	GameEngineDebug::LeakCheck();

	// ������ ����
	GameEngineWindow::WindowCreate(hInstance, "MainWindow");
	
	// ������ ���� ���� ���α׷��� ����� ���·� ���� �� �ֵ��� �����Լ� ȣ��
	GameEngineWindow::WindowLoop();

	return 0;
}


// 1. ���Ե��͸� ..\ �� ����
// 2. GameEngineWindow , Math �ڵ��ۼ�