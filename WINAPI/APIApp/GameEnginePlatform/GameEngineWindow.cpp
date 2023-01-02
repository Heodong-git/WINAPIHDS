#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>

// static ������ �ݵ�� ������ �־�� ����� �� �ִ�. 
HWND GameEngineWindow::hWnd = nullptr;

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

    hWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (!hWnd)
    {
        MsgAssert("������ Ŭ���� ������ �����߽��ϴ�.");
        return;
    }

    // ������â�� ����� ������ ������ ( â�� ����� �ʰ� ��׶��忡�� �����ϵ��� ������ ���� )
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    return;
}


int GameEngineWindow::WindowLoop()
{
    // ����Ű�ε�. �Ƚᵵ ������ ������ �ʴ´�.
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // ���� : ���� ��ȯ�Ǳ� ������ ���缭 �ٸ� ������ ������ �� ����. 
    // �񵿱� : ���� ��ȯ ���ο� ������� �ٸ� ������ ������ �� �ִ�.


    // �⺻ �޽��� �����Դϴ�:
    // GetMessage�� �� �����쿡 �������� ������� üũ����.
    // GetMessage�� �������� Ư���� ���� ���涧���� ���ߴ� �Լ��ΰ̴ϴ�.
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