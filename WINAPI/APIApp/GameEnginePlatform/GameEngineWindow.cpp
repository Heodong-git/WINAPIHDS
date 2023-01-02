#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>

// static 변수는 반드시 구현이 있어야 사용할 수 있다. 
HWND GameEngineWindow::hWnd = nullptr;

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

void GameEngineWindow::WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName)
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

    hWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (!hWnd)
    {
        MsgAssert("윈도우 클래스 생성에 실패했습니다.");
        return;
    }

    // 윈도우창을 띄워서 보여줄 것인지 ( 창을 띄우지 않고 백그라운드에서 동작하도록 설정도 가능 )
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    return;
}


int GameEngineWindow::WindowLoop()
{
    // 단축키인데. 안써도 문제가 되지는 않는다.
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 동기 : 어떠한 함수의 내부에서 값이 입력되어 반환되기 전까지 멈춰있음

    // 기본 메시지 루프입니다:
    // GetMessage는 내 윈도우에 무슨일이 생기는지 체크해줘.
    // GetMessage는 윈도우의 특별한 일이 생길때까지 멈추는 함수인겁니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        //if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        //{
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        //}
    }

    return (int)msg.wParam;
}


void GameEngineWindow::WindowSize(float4 _Size)
{
}

void GameEngineWindow::WindowPos(float4 _Pos)
{
}