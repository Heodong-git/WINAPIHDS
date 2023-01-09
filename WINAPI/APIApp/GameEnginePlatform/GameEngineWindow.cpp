#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineResources.h>

// static : �ݵ�� cpp ��ܿ� �������־����. 
HWND GameEngineWindow::HWnd = nullptr;
HDC GameEngineWindow::WindowBackBufferHdc = nullptr;
float4 GameEngineWindow::WindowSize = { 800, 600 };
float4 GameEngineWindow::WindowPos = { 100, 100 };
float4 GameEngineWindow::ScreenSize = { 800, 600 };
GameEngineImage* GameEngineWindow::BackBufferImage = nullptr;

// ���� ������ ������Ʈ ���¸� �������� ��Ÿ��. 
// false �� �ȴٸ� ���̻� ��������� �ݺ� X 
bool IsWindowUpdate = true;

// �����쿡 ���� �޼����� ���� �б�ó���ϴ� �Լ�
LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
        // �� ������â�� ���õǾ��ٸ�
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
        // Message�Լ��� 0�� �����ϰ� ������.
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
    // ������ Ŭ���� ����ü
    WNDCLASSEX wcex;

    // ����ü�� ũ��
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    // �޼���ó���Լ� 
    wcex.lpfnWndProc = MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    // nullptr �̶�� �⺻ ���������� �����ȴ�. 
    wcex.hIcon = nullptr; //LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // ���콺 Ŀ���� ����
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ��� 
    // ������ ��� �޴���, nullptr = �޴��� X 
    wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = "GameEngineWindowDefault";
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));



    // �Լ��� 0�� ��ȯ�Ѵٸ� ������ Ŭ���� ��� ����, ���α׷� ���� 
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("������ Ŭ���� ��Ͽ� �����߽��ϴ�.");
        return;
    }

    // hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.
    
    // Hwnd <-- ������ �ڵ鰪, ������ ���� 
    HWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (!HWnd)
    {
        MsgAssert("������ Ŭ���� ������ �����߽��ϴ�.");
        return;
    }

    // ������ �ڵ��� �־��ָ� �� �ڵ鰪�� ���� �����쿡 �׸��� �׸� �� �ִ� ������ �޾ƿ´�. (��ȭ��) 
    WindowBackBufferHdc = GetDC(HWnd);

    // ����� �̹��� ����
    BackBufferImage = new GameEngineImage();
    BackBufferImage->ImageCreate(WindowBackBufferHdc);

    // ������â�� ȭ�鿡 ������ ������ ( â�� ����� �ʰ� ��׶��忡�� �����ϵ��� ������ ���� )
    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    // ������â�� ũ��, ��ġ����
    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);
  
    return;
}

int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    // ������ ����Ǿ��� ��� �����۾��� ������ �Լ� ����
    if (nullptr != _Start)
    {
        _Start();
    }

    MSG msg;
    // ���� �Լ��� ����ɶ����� ���α׷��� �����.

    // GetMessage : �����Լ�, ��� ���� ��ȯ �Ǳ� ������ ���� 
    // ������ ��� �ؼ� �ڵ尡 �����ؾ� �ϱ� ������ ���Ӱ��� �Ÿ��� �� �޼���ó�����
    
    // ���� , ���ǹ��� ������ false �� �Ǹ� ��������
    while (IsWindowUpdate)
    {   
        // PeekMessage �Լ��� ��� �޼����� ���翩�ο� ������� �ݵ�� ���� ��ȯ�ȴ�. 
        // PM_REMOVE <-- �׿��ִ� �޼����� �����϶�� ���
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        { 
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (nullptr != _Loop)
            {
                _Loop();
            }
            
            // �޼����� �־��� �� ������ �����ߴٸ�
            // �Ʒ��� �ڵ尡 ������� �ʵ��� while ���� ��������.
            continue;
        }

        // ������ ����Ÿ�ӿ� ������ ���۽�Ų��. 
        if (nullptr != _Loop)
        {
            _Loop();
        }
    }

    // ���α׷� ����� ȣ��� �Լ�
    if (nullptr != _End)
    {
        _End();
    }

    // ������̹����� nullptr�� �ƴ϶�� ����
    if (nullptr != BackBufferImage)
    {
        delete BackBufferImage;
        BackBufferImage = nullptr;
    }

    return (int)msg.wParam;
}

void GameEngineWindow::SettingWindowSize(float4 _Size)
{
    // ������â�� ����� ��� Ÿ��Ʋ�ٿ� �������� ����Ͽ� ũ�⸦ �������־�� �Ѵ�. 
    // RECT ����ü : left, top, right, bottom �� ���� ������ �� �ִ� ����ü
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    // ���ϴ� ������ â�� ũ�⸦ ����
    // ���ڷ� ���� �� ex) 800, 600 
    ScreenSize = _Size;

    // ���ϴ� ũ���� ������ ������ Ÿ��Ʋ�ٱ��� ����� ũ�⸦ ����ü ������ ��ȯ���ش�. 
    // ex) 800, 600 �� �־��ٸ� Ÿ��Ʋ�ٱ��� ����� ������â ��ü�� ũ�⸦ ���ؼ� ��ȯ��.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    // ���� �����Ǵ� �������� ũ�� ( �޴��ٰ� ���Ե� ũ�� ) 
    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };
    
    // 0�� �־��ָ� ������ ũ�⸦ ����
    // ZORDER : ������â�� ���� ������ �ǹ�
    // ���� ������ �������� ũ�⸦ �־��ְ� â�� �ٽ� �����Ѵ�. 
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);  
}

void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    // ������ â�� ������ ��ġ ����
    WindowPos = _Pos;

    // �����츦 ���� ���ϴ� ��ǥ��, ���ϴ� ũ��� ���� 
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}
