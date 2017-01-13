// layerwindowtray.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "layerwindowtray.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND hWndActive;								// ���� Ȱ��ȭ�� â�Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK		EnumWindowsProc(HWND hWnd, LPARAM lparam);
BOOL CALLBACK		EnumWindowsProcBack(HWND hWnd, LPARAM lparam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.


	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAYERWINDOWTRAY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAYERWINDOWTRAY));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lparam) {

	// �θ� ����ȭ������
	if (GetParent(hWnd) == 0) {
		// �ּ�ȭ���� Ȱ��ȭ����
		if (!IsIconic(hWnd)) {
			// �̸� ���̰� �ִ���
			if (GetWindowTextLength(hWnd) > 0) {
				// set WS_EX_LAYERED on this Window
				SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
				// Current active windows ALPHA 95%, else windows 70%
				if (hWnd == hWndActive) {
					SetLayeredWindowAttributes(hWnd, 0, (255 * 95) / 100, LWA_ALPHA);
				}
				else {
					SetLayeredWindowAttributes(hWnd, 0, (255 * 70) / 100, LWA_ALPHA);
				}
			}
		}
	}
	return TRUE;
}

BOOL CALLBACK EnumWindowsProcBack(HWND hWnd, LPARAM lparam) {
	// �θ� ����ȭ������
	if (GetParent(hWnd) == 0) {
		// �ּ�ȭ���� Ȱ��ȭ����
		if (!IsIconic(hWnd)) {
			// �̸� ���̰� �ִ���
			if (GetWindowTextLength(hWnd) > 0) {
				// Remove WS_EX_LAYERED from this Window styles
				SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | ~WS_EX_LAYERED);
				// Ask the window and its children to repaint(???)
				//RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
				// Current active windows ALPHA 95% 
				SetLayeredWindowAttributes(hWnd, 0, (255 * 100) / 100, LWA_ALPHA);
			}
		}
	}
	return TRUE;
}

//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAYERWINDOWTRAY));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAYERWINDOWTRAY);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	// TODO: Make this window substitute for Tray Icon with background process.
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		100, 100, 0, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		SetTimer(hWnd,						// handle to main window 
			1,								// timer identifier 
			500,							// 0.5-second interval 
			(TIMERPROC)NULL);               // no timer callback 
		break;
	case WM_TIMER: 
	{
		// Get Current Active Window
		hWndActive = GetForegroundWindow();

		// All Windows Iteration
		EnumWindows(EnumWindowsProc, NULL);
	}
    break;
    case WM_DESTROY:
		EnumWindows(EnumWindowsProcBack, NULL);
		KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}