#include <Windows.h>
// ������ ������ ���ؼ� ��� ������Ʈ���� ������ �ִ��� �� �� �ְ� �ۼ�
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>


// �Ӽ� : ���������� -> â���� �ٲ��ָ� ������� WinMain ���� �������Լ� ����
int main()
{
	// ��üũ
	GameEngineDebug::LeakCheck();

	// ������ ����
	GameEngineWindow::WindowCreate();
	

	return 0;
}


// 1. ���Ե��͸� ..\ �� ����
// 2. GameEngineWindow , Math �ڵ��ۼ�