#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineInput.h"

// static : 반드시 cpp 상단에 구현해주어야함. 
HWND GameEngineWindow::HWnd = nullptr;
HDC GameEngineWindow::WindowBackBufferHdc = nullptr;
float4 GameEngineWindow::WindowSize = { 800, 600 };
float4 GameEngineWindow::WindowPos = { 100, 100 };
float4 GameEngineWindow::ScreenSize = { 800, 600 };
GameEngineImage* GameEngineWindow::BackBufferImage = nullptr;
GameEngineImage* GameEngineWindow::DoubleBufferImage = nullptr;

// 현재 윈도우 업데이트 상태를 전역으로 나타냄. 
// false 가 된다면 더이상 윈도우루프 반복 X 
bool GameEngineWindow::IsWindowUpdate = true;

// 윈도우에 들어온 메세지에 따라 분기처리하는 함수
LRESULT CALLBACK GameEngineWindow::MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
        // 내 윈도우창이 선택되었다면
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
    case WM_KEYDOWN:
    {
        GameEngineInput::IsAnyKeyOn();
        break;
    }
    case WM_DESTROY:
    {
        // Message함수가 0을 리턴하게 만들어라.
        PostQuitMessage(0); 
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
    // 윈도우 클래스 구조체
    WNDCLASSEX wcex;

    // 구조체의 크기
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    // 메세지처리함수 
    wcex.lpfnWndProc = &GameEngineWindow::MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    // nullptr 이라면 기본 아이콘으로 설정된다. 
    wcex.hIcon = nullptr; //LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // 마우스 커서의 형태
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 흰색 
    // 윈도우 상단 메뉴바, nullptr = 메뉴바 X 
    wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = "GameEngineWindowDefault";
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));



    // 함수가 0을 반환한다면 윈도우 클래스 등록 실패, 프로그램 종료 
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("윈도우 클래스 등록에 실패했습니다.");
        return;
    }

    // hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
    
    // Hwnd <-- 윈도우 핸들값, 윈도우 생성 
    HWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (!HWnd)
    {
        MsgAssert("윈도우 클래스 생성에 실패했습니다.");
        return;
    }

    // 윈도우 핸들을 넣어주면 그 핸들값을 가진 윈도우에 그림을 그릴 수 있는 권한을 받아온다. 
    WindowBackBufferHdc = GetDC(HWnd);
    // 윈도우창을 화면에 보여줄 것인지 ( 창을 띄우지 않고 백그라운드에서 동작하도록 설정도 가능 )
    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    // 윈도우창의 크기, 위치설정
    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    // 백버퍼 이미지 생성
    BackBufferImage = new GameEngineImage();
    BackBufferImage->ImageCreate(WindowBackBufferHdc);
  
    return;
}

// 더블버퍼 클리어
void GameEngineWindow::DoubleBufferClear()
{
    DoubleBufferImage->ImageClear();
}

// 현재 더블버퍼에 그려져있는 이미지를 백버퍼에 출력한다. 
void GameEngineWindow::DoubleBufferRender()
{
    //static GameEngineImage* BackBufferImage;
    //static GameEngineImage* DoubleBufferImage;
    BackBufferImage->BitCopy(DoubleBufferImage, WindowSize.half(), WindowSize);
}

int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    // 게임이 실행되었을 경우 사전작업을 수행할 함수 실행
    if (nullptr != _Start)
    {
        _Start();
    }

    MSG msg;
    // 동기 함수가 종료될때까지 프로그램이 멈춘다.

    // GetMessage : 동기함수, 어떠한 값이 반환 되기 전까지 멈춤 
    // 게임은 계속 해서 코드가 동작해야 하기 때문에 게임과는 거리가 먼 메세지처리방식
    
    // 루프 , 조건문의 변수가 false 가 되면 루프종료
    while (IsWindowUpdate)
    {   
        // PeekMessage 함수의 경우 메세지의 존재여부에 상관없이 반드시 값이 반환된다. 
        // PM_REMOVE <-- 쌓여있는 메세지를 삭제하라는 명령
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        { 
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (nullptr != _Loop)
            {
                _Loop();
            }
            
            GameEngineInput::IsAnyKeyOff();

            // 메세지가 있었을 때 루프를 실행했다면
            // 아래쪽 코드가 실행되지 않도록 while 문의 시작으로.
            continue;
        }

        // 윈도우 데드타임에 게임을 동작시킨다. 
        if (nullptr != _Loop)
        {
            _Loop();
        }

        GameEngineInput::IsAnyKeyOff();
    }

    // 프로그램 종료시 호출될 함수
    if (nullptr != _End)
    {
        _End();
    }

    // 백버퍼이미지가 nullptr이 아니라면 제거
    if (nullptr != BackBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;

        delete BackBufferImage;
        BackBufferImage = nullptr;
    }

    return (int)msg.wParam;
}

void GameEngineWindow::SettingWindowSize(float4 _Size)
{
    // 윈도우창이 실행될 경우 타이틀바와 프레임을 고려하여 크기를 설정해주어야 한다. 
    // RECT 구조체 : left, top, right, bottom 의 값을 저장할 수 있는 구조체
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    // 원하는 윈도우 창의 크기를 저장
    // 인자로 들어온 값 ex) 800, 600 
    ScreenSize = _Size;

    // 원하는 크기의 변수를 넣으면 타이틀바까지 고려한 크기를 구조체 변수에 반환해준다. 
    // ex) 800, 600 을 넣었다면 타이틀바까지 고려한 윈도우창 전체의 크기를 구해서 반환함.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    // 실제 생성되는 윈도우의 크기 ( 메뉴바가 포함된 크기 ) 
    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };
    
    // 0을 넣어주면 기존의 크기를 유지
    // ZORDER : 윈도우창의 정렬 기준을 의미
    // 실제 생성될 윈도우의 크기를 넣어주고 창을 다시 설정한다. 
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);  

    // 화면크기가 조정된다면 더블버퍼도 다시 만들어주어야한다. 
    if (nullptr != DoubleBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;
    }

    DoubleBufferImage = new GameEngineImage();
    DoubleBufferImage->ImageCreate(ScreenSize);

}

void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    // 윈도우 창이 생성될 위치 저장
    WindowPos = _Pos;

    // 윈도우를 내가 원하는 좌표값, 원하는 크기로 세팅 
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}

float4 GameEngineWindow::GetMousePosition()
{
    POINT MoniterPoint;
    LPPOINT PointPtr = &MoniterPoint;
    GetCursorPos(PointPtr);
    ScreenToClient(HWnd, PointPtr);

    return { static_cast<float>(MoniterPoint.x),static_cast<float>(MoniterPoint.y) };
}