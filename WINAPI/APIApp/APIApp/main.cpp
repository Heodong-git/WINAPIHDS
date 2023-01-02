#include <Windows.h>
// 앞쪽의 폴더를 통해서 어느 프로젝트까지 연관이 있는지 알 수 있게 작성
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>


// 속성 : 하위스시템 -> 창으로 바꿔주면 윈도우식 WinMain 으로 진입점함수 변경
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)

{
	// 릭체크
	GameEngineDebug::LeakCheck();

	// 윈도우 생성
	GameEngineWindow::WindowCreate(hInstance, "MainWindow");
	
	// 윈도우 생성 이후 프로그램이 실행된 상태로 있을 수 있도록 루프함수 호출
	GameEngineWindow::WindowLoop();

	return 0;
}


// 1. 포함디렉터리 ..\ 로 변경
// 2. GameEngineWindow , Math 코드작성