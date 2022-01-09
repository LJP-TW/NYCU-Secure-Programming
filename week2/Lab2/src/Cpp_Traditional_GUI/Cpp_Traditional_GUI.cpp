// Cpp_Traditional_GUI.cpp : 定義應用程式的進入點。
//

#include "framework.h"
#include "Cpp_Traditional_GUI.h"
#include <strsafe.h>

#define MAX_LOADSTRING 100

//  00 77
// 1c 8  6
// 1 c8  6
//  99cbb
// 2  ac 5
// 2  a c5
//  33 44

#define GRID 5
#define LINE_0(hdc, x, y) do { MoveToEx(hdc, x, y, NULL); \
                               LineTo(hdc, x + GRID, y);} while (0);
#define LINE_1(hdc, x, y) do { MoveToEx(hdc, x, y, NULL); \
                               LineTo(hdc, x, y + GRID);} while (0);
#define LINE_2(hdc, x, y) do { MoveToEx(hdc, x, y + GRID, NULL); \
                               LineTo(hdc, x, y + GRID * 2);} while (0);
#define LINE_3(hdc, x, y) do { MoveToEx(hdc, x, y + GRID * 2, NULL); \
                               LineTo(hdc, x + GRID, y + GRID * 2);} while (0);
#define LINE_4(hdc, x, y) do { MoveToEx(hdc, x + GRID, y + GRID * 2, NULL); \
                               LineTo(hdc, x + GRID * 2, y + GRID * 2);} while (0);
#define LINE_5(hdc, x, y) do { MoveToEx(hdc, x + GRID * 2, y + GRID * 2, NULL); \
                               LineTo(hdc, x + GRID * 2, y + GRID);} while (0);
#define LINE_6(hdc, x, y) do { MoveToEx(hdc, x + GRID * 2, y + GRID, NULL); \
                               LineTo(hdc, x + GRID * 2, y);} while (0);
#define LINE_7(hdc, x, y) do { MoveToEx(hdc, x + GRID * 2, y, NULL); \
                               LineTo(hdc, x + GRID, y);} while (0);
#define LINE_8(hdc, x, y) do { MoveToEx(hdc, x + GRID, y, NULL); \
                               LineTo(hdc, x + GRID, y + GRID);} while (0);
#define LINE_9(hdc, x, y) do { MoveToEx(hdc, x + GRID, y + GRID, NULL); \
                               LineTo(hdc, x, y + GRID);} while (0);
#define LINE_a(hdc, x, y) do { MoveToEx(hdc, x + GRID, y + GRID, NULL); \
                               LineTo(hdc, x + GRID, y + GRID * 2);} while (0);
#define LINE_b(hdc, x, y) do { MoveToEx(hdc, x + GRID, y + GRID, NULL); \
                               LineTo(hdc, x + GRID * 2, y + GRID);} while (0);
#define LINE_b(hdc, x, y) do { MoveToEx(hdc, x + GRID, y + GRID, NULL); \
                               LineTo(hdc, x + GRID * 2, y + GRID);} while (0);
#define LINE_c(hdc, x, y) do { MoveToEx(hdc, x, y, NULL); \
                               LineTo(hdc, x + GRID * 2, y + GRID * 2);} while (0);


// 全域變數:
HINSTANCE hInst;                                // 目前執行個體
WCHAR szTitle[MAX_LOADSTRING];                  // 標題列文字
WCHAR szWindowClass[MAX_LOADSTRING];            // 主視窗類別名稱

// 這個程式碼模組所包含之函式的向前宣告:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置程式碼。

    // 將全域字串初始化
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CPPTRADITIONALGUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 執行應用程式初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CPPTRADITIONALGUI));

    MSG msg;

    // 主訊息迴圈:
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



//
//  函式: MyRegisterClass()
//
//  用途: 註冊視窗類別。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CPPTRADITIONALGUI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CPPTRADITIONALGUI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    
    return RegisterClassExW(&wcex);
}

//
//   函式: InitInstance(HINSTANCE, int)
//
//   用途: 儲存執行個體控制代碼並且建立主視窗
//
//   註解:
//
//        在這個函式中，我們將執行個體控制代碼儲存在全域變數中，
//        並建立及顯示主程式視窗。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 將執行個體控制代碼儲存在全域變數中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   HWND hTextAccount = CreateWindowW(_T("STATIC"), _T("帳號: "), WS_VISIBLE | WS_CHILD | SS_LEFT, 20, 30, 60, 20, hWnd, NULL, NULL, NULL);
   HWND hEditAccount = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE, 80, 30, 140, 20, hWnd, (HMENU)IDC_EDIT_ACCOUNT, NULL, NULL);
   HWND hTextPasswd  = CreateWindowW(_T("STATIC"), _T("密碼: "), WS_VISIBLE | WS_CHILD | SS_LEFT, 220, 30, 60, 20, hWnd, NULL, NULL, NULL);
   HWND hEditPasswd  = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE, 280, 30, 140, 20, hWnd, (HMENU)IDC_EDIT_PASSWD, NULL, NULL);
   HWND hButtOk      = CreateWindowW(_T("BUTTON"), _T("OK"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 20, 60, 70, 35, hWnd, (HMENU)IDC_BUTTON_OK, NULL, NULL);
   
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函式: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  用途: 處理主視窗的訊息。
//
//  WM_COMMAND  - 處理應用程式功能表
//  WM_PAINT    - 繪製主視窗
//  WM_DESTROY  - 張貼結束訊息然後傳回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR buf1[0x101] = { '\0' };
    TCHAR buf2[0x101] = { '\0' };
    HWND hEditAccount;
    HWND hEditPasswd;
    int x, y;
    static bool draw = false;

    switch (message)
    {
    case WM_CREATE: 
        {
            MessageBoxW(hWnd, _T("沒有權限的人是過不了的"), _T("You should not pass"), MB_OK);
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);

            // 剖析功能表選取項目:
            switch (wmId)
            {
            case IDC_BUTTON_OK:
                hEditAccount = GetDlgItem(hWnd, IDC_EDIT_ACCOUNT);
                GetWindowText(hEditAccount, buf1, 0x100);
                hEditPasswd  = GetDlgItem(hWnd, IDC_EDIT_PASSWD);
                GetWindowText(hEditPasswd , buf2, 0x100);
                if (!wcscmp(buf1, _T("亞洲統神")) && !wcscmp(buf2, _T("toyz2k7e.3"))) {
                    // Pass
                    draw = true;
                    RedrawWindow(hWnd, 0, 0, RDW_INVALIDATE);
                    break;
                }
                // Fail
                MessageBoxW(hWnd, _T("登入失敗"), _T("錯誤"), MB_OK);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            if (draw) {
                HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
                HGDIOBJ hOldPen = SelectObject(hdc, hPen);
                // TODO: 在此新增任何使用 hdc 的繪圖程式碼...

                // F
                x = 20;
                y = 100;
                LINE_0(hdc, x, y);
                LINE_1(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_9(hdc, x, y);
                LINE_b(hdc, x, y);

                // L
                x += (GRID*2 + 5);
                LINE_1(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);

                // A
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_1(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_5(hdc, x, y);
                LINE_6(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_9(hdc, x, y);
                LINE_b(hdc, x, y);

                // G
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_1(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);
                LINE_5(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_b(hdc, x, y);

                // {
                x += (GRID * 2 + 5); 
                LINE_4(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_8(hdc, x, y);
                LINE_9(hdc, x, y);
                LINE_a(hdc, x, y);

                // W
                x += (GRID * 2 + 5);
                LINE_1(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);
                LINE_5(hdc, x, y);
                LINE_6(hdc, x, y);
                LINE_a(hdc, x, y);
                
                // I
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_8(hdc, x, y);
                LINE_a(hdc, x, y);

                // N
                x += (GRID * 2 + 5);
                LINE_1(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_5(hdc, x, y);
                LINE_6(hdc, x, y);
                LINE_c(hdc, x, y);

                // 3
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);
                LINE_5(hdc, x, y);
                LINE_6(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_9(hdc, x, y);
                LINE_b(hdc, x, y);

                // 2
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);
                LINE_6(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_9(hdc, x, y);
                LINE_b(hdc, x, y);

                // _
                x += (GRID * 2 + 5);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);

                // G
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_1(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);
                LINE_5(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_b(hdc, x, y);

                // U
                x += (GRID * 2 + 5);
                LINE_1(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);
                LINE_5(hdc, x, y);
                LINE_6(hdc, x, y);

                // I
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_8(hdc, x, y);
                LINE_a(hdc, x, y);

                // _
                x += (GRID * 2 + 5);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);

                // S
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_c(hdc, x, y);

                // O
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_1(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);
                LINE_5(hdc, x, y);
                LINE_6(hdc, x, y);
                LINE_7(hdc, x, y);

                // _
                x += (GRID * 2 + 5);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);

                // P
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_1(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_6(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_9(hdc, x, y);
                LINE_b(hdc, x, y);

                // A
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_1(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_5(hdc, x, y);
                LINE_6(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_9(hdc, x, y);
                LINE_b(hdc, x, y);

                // I
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_4(hdc, x, y);
                LINE_7(hdc, x, y);
                LINE_8(hdc, x, y);
                LINE_a(hdc, x, y);

                // N
                x += (GRID * 2 + 5);
                LINE_1(hdc, x, y);
                LINE_2(hdc, x, y);
                LINE_5(hdc, x, y);
                LINE_6(hdc, x, y);
                LINE_c(hdc, x, y);

                // }
                x += (GRID * 2 + 5);
                LINE_0(hdc, x, y);
                LINE_3(hdc, x, y);
                LINE_8(hdc, x, y);
                LINE_a(hdc, x, y);
                LINE_b(hdc, x, y);

                SelectObject(hdc, hOldPen);
                DeleteObject(hPen);
            }

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// [關於] 方塊的訊息處理常式。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
