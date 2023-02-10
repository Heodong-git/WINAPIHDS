// 이전
// 현재 포함 디렉터리가 경로 + ..\ 로 설정되어 있기 때문에 
// 이전폴더에 있는 어떠한 폴더 / 헤더파일로 include 가능
#include <Windows.h>
#include <MegaManContents/MegaManCore.h>
#include <GameEngineBase/GameEngineTime.h>

// 속성 : 하위시스템 -> 창으로 바꿔주면 윈도우식 WinMain 으로 진입점함수 변경	
// 진입점인자(메인파라미터) , OS가 인자를 채워주게 된다.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)

{
	// 실행
	// 내부에서 원하는 해상도로 윈도우 생성
	// 루프 실행
	MegaManCore::GetInst().CoreStart(hInstance);
	return 0;
}

// 릭체크
//GameEngineDebug::LeakCheck();

// 윈도우 생성
//GameEngineWindow::WindowCreate(hInstance, "MainWindow", { 1360, 768 }, { 0, 0 });

// 프로그램 동작, 무한루프
// 인자로 함수포인터를 받아서 내부에서 함수를 실행시킨다. 
// 이런 형태의 동작방식을 callback 이라고 한다.
// callback 의 정의: 호출될 함수를 인자로 넘겨주고
// 다른 프로그램 혹은 다른 모듈에서 함수를 호출하여 실행하는 방법 
// 원하는 시점에 호출할 수 도 있고, 특정 시점에 호출할 수도 있다. 
// ( 특정 이벤트 발생시 호출 ) 
//GameEngineWindow::WindowLoop(TestGameStart, TestGameLoop, TestGameEnd);

// 20230102
// 1. 포함디렉터리 ..\ 로 변경 [완료]
// 2. GameEngineWindow , Math 코드작성 [완료]
// 3. 공부 <

// 20230103
// 1. Math , Window 변경 [완료] 

// 20230104
// 1. GetMessage -> PickMessage 
// 2. Window
// 3. main 
// 4. Core + MegaManCore
// 5. Level 생성 

// 20230104 시점까지의 동작방식
// static 으로 구현되어 있는 MegaManCore 클래스가 프로그램 실행시 데이터 영역에 만들어지고 
// 진입점함수에서 Core클래스의 CoreStart 함수를 통해
// 윈도우를 생성, 윈도우 루프를 동작시킨다. 
// 루프를 동작시킬 때 에는 생성된 Core 클래스의 부모인 클래스의 
// GlobalStart, Update, End 함수를 인자로 넣어주고 
// (글로벌 함수는 생성된 코어의 Start, Update, End 함수를 호출함)
// 내부에서 원하는 시점에 동작시키게 된다. ( call back 방식이라고 함 ) 
// 이렇게 작성하는 이유는 엔진과 컨텐츠를 완전하게 분리시키기 위함이다.
// Start 함수 동작시 , 현재 소유하고 있는 map 에 컨텐츠 Level 들을 모두 생성 후 저장하고
// 화면에 보여줄 MainLevel 을 선택한다. 

// 20230105 
// 1. Core, Level , Actor, Player ,  Math 
// 2. 포인터를 인자로 받는다면 반드시 null 검사 
