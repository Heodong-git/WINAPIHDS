#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>

// static ������ �ݵ�� ������ �־�� ����� �� �ִ�. 
// ������â�� �ϳ��� �ѱ� ���ؼ� static ���� ����Ǿ���. 
// cpp ��ܿ� ����
HWND GameEngineWindow::HWnd = nullptr;
HDC GameEngineWindow::DrawHdc = nullptr;
float4 GameEngineWindow::WindowSize = { 800, 600 };
float4 GameEngineWindow::WindowPos = { 100, 100 };
float4 GameEngineWindow::ScreenSize = { 800, 600 };

bool IsWindowUpdate = true;

// � �޼����� ���԰�, �޼����� ���� �б�ó���� �����ϴ� �Լ� 
LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
        // �� �����찡 ���õǾ���.
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

        // �ش� ������ false �� ������ְ� �Ǹ�
        // ������ �ڵ带 �����ְ� �ִ� while ���� ���ǿ� ���� �ʱ� ������ ���α׷��� ����ȴ�. 
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
    // �����찡 ������� ������ �������� ������ ����Ǿ��ִ� ����ü
    WNDCLASSEX wcex;

    // ����ü�� ũ��
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    // �޼���ó�� �Լ� = MessageFunction, �Էµ� �޼����� �ش� �Լ����� ó��
    wcex.lpfnWndProc = MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    // nullptr �̶�� �������� �⺻ ���������� ����
    wcex.hIcon = nullptr; //LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    // ���콺 Ŀ���� ����
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ��� 
    // ������â�� ��ܿ� ��ġ�� �޴���, nullptr �� �־��� ��� �ٰ� �޴��� ���� X 
    wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    // 
    wcex.lpszClassName = "GameEngineWindowDefault";
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));



    // �Լ��� 0�� ��ȯ�ϰ� �� ��� ������ ��Ͽ� ������ ���̴�, ���α׷����� 
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("������ Ŭ���� ��Ͽ� �����߽��ϴ�.");
        return;
    }

    // hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    // 1000�� ���α׷��� �����츦 ����޶�� ��û�ߴ�.
    // ������� �ٽ� Ư�� �����̶�� �����찡 ��������ٰ� �츮���� �˷��ִµ�.
    // Ư�� ���ڷ� �νĵǴ� �츮�� �����쿡�� ũ�⺯�� ����

    HWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (!HWnd)
    {
        MsgAssert("������ Ŭ���� ������ �����߽��ϴ�.");
        return;
    }

    // ���� ������ �����쿡 �׸��� �׸� �� �ִ� ������ �޾ƿ´�.
    // ������ �ڵ鰪�� ���ڷ� �־��ְ� �Ǹ� �� �������� DC�� �޾ƿ� �� �ִ�. 
    DrawHdc = GetDC(HWnd);

    // ������â�� ȭ�鿡 ������ ������ ( â�� ����� �ʰ� ��׶��忡�� �����ϵ��� ������ ���� )
    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    // ������â�� ������ ��ġ, �ػ󵵼���
    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    return;
}



int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    // ����Ű�ε�. �Ƚᵵ ������ ������ �ʴ´�.
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
    
    // ���� ���۽� ������ �Լ��� �޾ƿͼ� ȣ��
    if (nullptr != _Start)
    {
        _Start();
    }

    MSG msg;

    // ���� �Լ��� ����ɶ����� ���α׷��� �����.

    // �⺻ �޽��� �����Դϴ�:
    // GetMessage�� �� �����쿡 �������� ������� üũ����.
    // GetMessage�� �������� Ư���� ���� �������� ���ߴ� �Լ��ΰ̴ϴ�.
    // ������ false ��� ���α׷��� ����Ǵ� ���·� �ۼ�
    while (IsWindowUpdate)
    {
        //if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        //{
        //}

        // ������ �޼����� ó���Ѵ�.
        // GetMessage�� �����Լ��̱� ������ ���ʿ� ������ ����� �ִ� �޼��� ����� �ƴϴ�
        // => ������ �������� ���ƾ� �ϴµ�
        // GetMessage��� �Լ��� => �����쿡 �������� ����� ���ϵǴ� �Լ�
        // �����쿡 �������� ����� ������ �Ѵ�.
        if (GetMessage(&msg, nullptr, 0, 0))
        {
            // ������ ������ Loop
            if (nullptr != _Loop)
            {
                _Loop();
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // ����ǰ� �ִ� ���α׷��� ����� ���Ŀ� ������ �Լ��� �޾ƿԱ� ������ 
    // �� �Լ��� ȣ��
    if (nullptr != _End)
    {
        _End();
    }

    return (int)msg.wParam;
}

void GameEngineWindow::SettingWindowSize(float4 _Size)
{
    // ������â�� ����� ��� Ÿ��Ʋ�ٿ� �������� ����Ͽ� ũ�⸦ �������־�� �Ѵ�. 
    // RECT ����ü : left, top, right, bottom �� ���� ������ �� �ִ� ����ü
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    // ���� ���ϴ� â�� ũ�⸦ ����
    ScreenSize = _Size;

    // ���� ���ϴ� ũ�⸦ ������ Ÿ��Ʋ�ٱ��� ����� ũ�⸦ ����ü ������ ��ȯ���ش�. 
    // ex) 800, 600 �� �־��ٸ� Ÿ��Ʋ�ٱ��� ����� ������â ��ü�� ũ�⸦ ���ؼ� ��ȯ��.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    // ������ �����Ǵ� �������� ũ�� ( �޴��� ���� ���Ե� ũ�� ) 
    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };
    
    // 0�� �־��ָ� ������ ũ�⸦ �����Ѵ�.
    // ���� ���ϴ� â�� ũ�Ⱑ WindowSize ������ ����Ǿ� �ֱ� ������
    // �ش� ������ Ȱ���Ͽ� ������â�� �ٽ� �������ش�. 
    // ZORDER : ������â�� ���� ������ �ǹ�
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);  
}

void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    // ������â�� ������ ������ġ�� ����
    WindowPos = _Pos;
    // HWnd �ڵ鰪�� ���� �����츦 ���� ���ϴ� ��ǥ��, ���ϴ� ũ��� ���� 
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}
