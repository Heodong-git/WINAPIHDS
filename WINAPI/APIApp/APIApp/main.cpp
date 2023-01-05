// ����
// ���� ���� ���͸��� ��� + ..\ �� �����Ǿ� �ֱ� ������ 
// ���������� �ִ� ��� ���� / ������Ϸ� include ����
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <MegaManContents/MegaManCore.h>

// �Ӽ� : �����ý��� -> â���� �ٲ��ָ� ������� WinMain ���� �������Լ� ����
// ����������(�����Ķ����) , OS�� ���ڸ� ä���ְ� �ȴ�.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)

	// static ������ �����Ϳ����� �޸𸮰� ��������� ���α׷� ����ÿ� �޸𸮰� �����ȴ�.
	// �̹� �� ������ Core �� ������ ������ ���������. 
{
	// ����
	// ���ο��� ���ϴ� �ػ󵵷� ������ ����
	// ���� ����
	MegaManCore::GetInst().CoreStart(hInstance);
	return 0;
}

// ��üũ
//GameEngineDebug::LeakCheck();

// ������ ����
//GameEngineWindow::WindowCreate(hInstance, "MainWindow", { 1360, 768 }, { 0, 0 });

// ���α׷� ����, ���ѷ���
// ���ڷ� �Լ������͸� �޾Ƽ� ���ο��� �Լ��� �����Ų��. 
// �̷� ������ ���۹���� callback �̶�� �Ѵ�.
// callback �� ����: ȣ��� �Լ��� ���ڷ� �Ѱ��ְ�
// �ٸ� ���α׷� Ȥ�� �ٸ� ��⿡�� �Լ��� ȣ���Ͽ� �����ϴ� ��� 
// ���ϴ� ������ ȣ���� �� �� �ְ�, Ư�� ������ ȣ���� ���� �ִ�. 
// ( Ư�� �̺�Ʈ �߻��� ȣ�� ) 
//GameEngineWindow::WindowLoop(TestGameStart, TestGameLoop, TestGameEnd);

// 20230102
// 1. ���Ե��͸� ..\ �� ���� [�Ϸ�]
// 2. GameEngineWindow , Math �ڵ��ۼ� [�Ϸ�]
// 3. ���� <

// 20230103
// 1. Math , Window ���� [�Ϸ�] 

// 20230104
// 1. GetMessage -> PickMessage 
// 2. Window
// 3. main 
// 4. Core + MegaManCore
// 5. Level ���� 

// 20230104 ���������� ���۹��
// static ���� �����Ǿ� �ִ� MegaManCore Ŭ������ ���α׷� ����� ������ ������ ��������� 
// �������Լ����� CoreŬ������ CoreStart �Լ��� ����
// �����츦 ����, ������ ������ ���۽�Ų��. 
// ������ ���۽�ų �� ���� ������ Core Ŭ������ �θ��� Ŭ������ 
// GlobalStart, Update, End �Լ��� ���ڷ� �־��ְ� 
// (�۷ι� �Լ��� ������ �ھ��� Start, Update, End �Լ��� ȣ����)
// ���ο��� ���ϴ� ������ ���۽�Ű�� �ȴ�. ( call back ����̶�� �� ) 
// �̷��� �ۼ��ϴ� ������ ������ �������� �����ϰ� �и���Ű�� �����̴�.
// Start �Լ� ���۽� , ���� �����ϰ� �ִ� map �� ������ Level ���� ��� ���� �� �����ϰ�
// ȭ�鿡 ������ MainLevel �� �����Ѵ�. 

// 20230105 
// 1. Core, Level , Actor, Player ,  Math 
// 2. �����͸� ���ڷ� �޴´ٸ� �ݵ�� null �˻� 
