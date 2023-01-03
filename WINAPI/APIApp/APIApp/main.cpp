#include <Windows.h>
// 이전
// 현재 포함 디렉터리가 경로 + ..\ 로 설정되어 있기 때문에 
// 이전폴더에 있는 어떠한 폴더 / 헤더파일로 include 가 가능
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// 이부분은 이제 내 게임을 만들기시작하면
// 게임시작시 호출될 함수, 게임루프, 게임종료시 호출될 함수로 대체. 
void TestGameStart()
{
	int a = 0;
}

int x = 0;

void TestGameLoop()
{
	// 화면에 그림을 그려주는 함수입니다.

	++x;

	Rectangle(GameEngineWindow::GetDrawHdc(), x, 0, 100 + x, 100);

	// 몬스터가 움직이게 만들고
	// 플레이어가 움직이게 만들어야 한다.
	int a = 0;
}

void TestGameEnd()
{
	int a = 0;
}


// 속성 : 하위시스템 -> 창으로 바꿔주면 윈도우식 WinMain 으로 진입점함수 변경
// 진입점인자(메인파라미터) , OS가 인자를 채워주게 된다.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)

{
	// 릭체크
	GameEngineDebug::LeakCheck();

	// 윈도우 생성
	GameEngineWindow::WindowCreate(hInstance, "MainWindow", {1360, 768}, { 0, 0});
	
	// 프로그램 동작, 무한루프
	// 인자로 함수포인터를 받아서 내부에서 함수를 실행시킨다. 
	// 이런 형태의 동작방식을 callback 이라고 한다.
	// callback 의 정의: 호출될 함수를 인자로 넘겨주고 ( 알려주고 )
	// 다른 프로그램 혹은 다른 모듈에서 함수를 호출하여 실행하는 방법 
	// 원하는 시점에 호출할 수 도 있고, 특정 시점에 호출할 수도 있다. 
	GameEngineWindow::WindowLoop(TestGameStart,TestGameLoop,TestGameEnd);

	return 0;
}



// 20230102
// 1. 포함디렉터리 ..\ 로 변경 [완료]
// 2. GameEngineWindow , Math 코드작성 [완료]
// 3. 공부 <

// 20230103
// 1. Math , Window 변경 [완료] 


