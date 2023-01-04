#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>

// static 변수는 반드시 구현이 있어야 사용할 수 있다. 
// 윈도우창을 하나만 켜기 위해서 static 으로 선언되었다. 
// cpp 상단에 구현
HWND GameEngineWindow::HWnd = nullptr;
HDC GameEngineWindow::DrawHdc = nullptr;
float4 GameEngineWindow::WindowSize = { 800, 600 };
float4 GameEngineWindow::WindowPos = { 100, 100 };
float4 GameEngineWindow::ScreenSize = { 800, 600 };

bool IsWindowUpdate = true;

// 어떤 메세지가 들어왔고, 메세지에 따라 분기처리를 진행하는 함수 
LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
        // 내 윈도우가 선택되었다.
    case WM_SETFOCUS:
    {
        int a = 0;
        break;
    }
    case WM_ACTIVATE:
    {
        int a = 0;
        break;
    }
    case WM_KILLFOCUS:
    {
        int a = 0;
        break;
    }
    case WM_DESTROY:
    {
        // Message함수가 0을 리턴하게 만들어라.
        PostQuitMessage(0);

        // 해당 변수를 false 로 만들어주게 되면
        // 무한히 코드를 돌려주고 있는 while 문의 조건에 맞지 않기 때문에 프로그램이 종료된다. 
        IsWindowUpdate = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }

    return 0;
}

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
}

void GameEngineWindow::WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos)
{
    // 윈도우가 어떤식으로 구성될 것인지의 내용이 저장되어있는 구조체
    WNDCLASSEX wcex;

    // 구조체의 크기
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    // 메세지처리 함수 = MessageFunction, 입력된 메세지는 해당 함수에서 처리
    wcex.lpfnWndProc = MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    // nullptr 이라면 윈도우의 기본 아이콘으로 설정
    wcex.hIcon = nullptr; //LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // 마우스 커서의 형태
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 흰색 
    // 윈도우창의 상단에 위치한 메뉴바, nullptr 을 넣어줄 경우 바가 메뉴바 생성 X 
    wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    // 
    wcex.lpszClassName = "GameEngineWindowDefault";
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));



    // 함수가 0을 반환하게 될 경우 윈도우 등록에 실패한 것이다, 프로그램종료 
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("윈도우 클래스 등록에 실패했습니다.");
        return;
    }

    // hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    // 1000번 프로그램이 윈도우를 띄워달라고 요청했다.
    // 윈도우는 다시 특정 숫자이라는 윈도우가 만들어졌다고 우리에게 알려주는데.
    // 특정 숫자로 인식되는 우리의 윈도우에게 크기변경 떠라

    HWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (!HWnd)
    {
        MsgAssert("윈도우 클래스 생성에 실패했습니다.");
        return;
    }

    // 내가 생성한 윈도우에 그림을 그릴 수 있는 권한을 받아온다.
    // 윈도우 핸들값을 인자로 넣어주게 되면 그 윈도우의 DC를 받아올 수 있다. 
    DrawHdc = GetDC(HWnd);

    
    // 윈도우창을 화면에 보여줄 것인지 ( 창을 띄우지 않고 백그라운드에서 동작하도록 설정도 가능 )
    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    // 윈도우창이 생성될 위치, 해상도설정
    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);
  
    return;
}



int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    // 단축키인데. 안써도 문제가 되지는 않는다.
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
    
    // 게임 시작시 동작할 함수를 받아와서 호출
    if (nullptr != _Start)
    {
        _Start();
    }

    MSG msg;

    // 동기 함수가 종료될때까지 프로그램이 멈춘다.

    // 기본 메시지 루프입니다:
    // GetMessage는 내 윈도우에 무슨일이 생기는지 체크해줘.
    // GetMessage는 윈도우의 특별한 일이 생길대까지 멈추는 함수인겁니다.
    // 변수가 false 라면 프로그램이 종료되는 형태로 작성
    while (IsWindowUpdate)
    {
        //if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        //{
        //}

        // 윈도우 메세지를 처리한다.
        // GetMessage는 동기함수이기 때문에 애초에 게임을 만들수 있는 메세지 방식이 아니다
        // => 게임은 쉴새없이 돌아야 하는데
        // GetMessage라는 함수는 => 윈도우에 무슨일이 생기면 리턴되는 함수
        // 윈도우에 무슨일이 생기게 만들어야 한다.

        // PeekMessage 함수의 경우 메세지의 존재여부에 상관없이 반드시 값이 반환된다. 
        // PM_REMOVE <-- 쌓여있는 메세지를 삭제하라는 명령

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        { 
            if (nullptr != _Loop)
            {
                _Loop();
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // 현시점 잘못된 코드, 내일 쌤이 변경해주시는거 보고 수정
        if (nullptr != _Loop)
        {
            _Loop();
        }
    }

    // 실행되고 있는 프로그램이 종료된 이후에 실행할 함수를 받아왔기 때문에 
    // 그 함수를 호출
    if (nullptr != _End)
    {
        _End();
    }

    return (int)msg.wParam;
}

void GameEngineWindow::SettingWindowSize(float4 _Size)
{
    // 윈도우창이 실행될 경우 타이틀바와 프레임을 고려하여 크기를 설정해주어야 한다. 
    // RECT 구조체 : left, top, right, bottom 의 값을 저장할 수 있는 구조체
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    // 내가 원하는 창의 크기를 저장
    ScreenSize = _Size;

    // 내가 원하는 크기를 넣으면 타이틀바까지 고려한 크기를 구조체 변수에 반환해준다. 
    // ex) 800, 600 을 넣었다면 타이틀바까지 고려한 윈도우창 전체의 크기를 구해서 반환함.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    // 실제로 생성되는 윈도우의 크기 ( 메뉴바 등이 포함된 크기 ) 
    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };
    
    // 0을 넣어주면 기존의 크기를 유지한다.
    // 내가 원하는 창의 크기가 WindowSize 변수에 저장되어 있기 때문에
    // 해당 변수를 활용하여 윈도우창을 다시 세팅해준다. 
    // ZORDER : 윈도우창의 정렬 기준을 의미
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);  
}

void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    // 윈도우창이 생성될 시작위치를 저장
    WindowPos = _Pos;
    // HWnd 핸들값을 가진 윈도우를 내가 원하는 좌표값, 원하는 크기로 세팅 
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}
