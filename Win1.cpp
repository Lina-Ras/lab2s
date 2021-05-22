#define _USE_MATH_DEFINES
#define MAX_LOADSTRING 100
#define WIDARROW 0.015  //arrow width k
#define HEIARROW 0.025  // arrow height k
#define AxisK 0.05
#define TimeD 0.05   //time delta
#define One 0.4
#define A 3
#define B 7
#define Radius 6 // ellipse

#include "framework.h"
#include "Win1.h"
#include <math.h>
#include <string>


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN1));

    MSG msg;

    // Main message loop:
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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

int GetWidth(HWND hWnd) {
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    auto width = clientRect.right - clientRect.left;
    return width;
}

int GetHeight(HWND hWnd) {
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    auto height = clientRect.bottom - clientRect.top;
    return height;
}

int GetX(HWND hWnd, double angle) {
    auto width = GetWidth(hWnd);
    int hw = width / 2;
    int x = sin(angle * A / B) * cos(angle) * hw * One + hw;
    return x;
}

int GetY(HWND hWnd, double angle) {
    auto width = GetWidth(hWnd);
    auto height = GetHeight(hWnd);
    int hw = width / 2;
    int hh = height / 2;
    int y = sin(angle * A / B) * sin(angle) * hw * One + hh;
    return y;
}

void PaintAxis(HWND hWnd, HDC hdc, PAINTSTRUCT ps) {
    LOGBRUSH lb;
    lb.lbColor = 0x000000;
    lb.lbStyle = BS_SOLID;

    HPEN axpen = ExtCreatePen(PS_GEOMETRIC | PS_DASH, 2, &lb, 0, NULL);

    auto width = GetWidth(hWnd);
    auto height = GetHeight(hWnd);
    int hw, hh;  //half width, half height

    SelectObject(hdc, axpen);
    hw = width / 2;     hh = height / 2;
    MoveToEx(hdc, 0, hh, NULL);
    LineTo(hdc, width, hh);
    MoveToEx(hdc, hw, 0, NULL);
    LineTo(hdc, hw, height);

    int wiArrow, hArrow;
    wiArrow = height * WIDARROW;   // width of the arrow
    hArrow = height * HEIARROW; // height of the arrow
    MoveToEx(hdc, width - hArrow, hh + wiArrow, NULL);
    LineTo(hdc, width, hh);
    MoveToEx(hdc, width - hArrow, hh - wiArrow, NULL);
    LineTo(hdc, width, hh);

    MoveToEx(hdc, hw + wiArrow, hArrow, NULL);
    LineTo(hdc, hw, 0);
    MoveToEx(hdc, hw - wiArrow, hArrow, NULL);
    LineTo(hdc, hw, 0);

    int LAxis = hw * AxisK;
    for (int one = 0; one < hw; one += hw * One) {
        MoveToEx(hdc, hw + one, hh - LAxis, NULL);
        LineTo(hdc, hw + one, hh + LAxis);
        MoveToEx(hdc, hw - one, hh - LAxis, NULL);
        LineTo(hdc, hw - one, hh + LAxis);
    }
    for (int one = 0; one < hh; one += hw * One) {
        MoveToEx(hdc, hw - LAxis, hh + one, NULL);
        LineTo(hdc, hw + LAxis, hh + one);
        MoveToEx(hdc, hw - LAxis, hh - one, NULL);
        LineTo(hdc, hw + LAxis, hh - one);
    }

    DeleteObject(axpen);
    return;
}

void PaintGraph(HWND hWnd, HDC hdc, PAINTSTRUCT ps, double t) {
    LOGBRUSH lb;
    lb.lbStyle = BS_SOLID;
    lb.lbColor = 0x70cc90;
    HPEN colpen = ExtCreatePen(PS_GEOMETRIC, 2, &lb, 0, NULL);

    auto width = GetWidth(hWnd);
    auto height = GetHeight(hWnd);
    int hw, hh;  //half width, half height

    hw = width / 2;     hh = height / 2;
    SelectObject(hdc, colpen);
    int x, y;
    MoveToEx(hdc, hw, hh, NULL);
    for (double angle = 0; angle <= t; angle += 0.025)
    {
        x = GetX(hWnd, angle);
        y = GetY(hWnd, angle);
        LineTo(hdc, x, y);
        MoveToEx(hdc, x, y, NULL);
    }
    DeleteObject(colpen);

    HBRUSH ballBrush = CreateSolidBrush(0xaff1f2);
    SelectObject(hdc, ballBrush);
    Ellipse(hdc, x - Radius, y - Radius, x + Radius, y + Radius);
    DeleteObject(ballBrush);
    return;
}

void TextCoords(HWND hWnd, HDC hdc, PAINTSTRUCT ps, double t) {

    auto width = GetWidth(hWnd);
    auto height = GetHeight(hWnd);
    int hw, hh;  //half width, half height
    hw = width / 2;     hh = height / 2;
    
    int x, y;
    x = GetX(hWnd, t);
    y = GetY(hWnd, t);

    WORD xm, ym, size;
    TCHAR tchar[80];

    xm = x;
    ym = y;
    size = wsprintf(tchar, TEXT("(%d, %d)"), xm, ym);

    static LOGFONT lf;
    lf.lfHeight = 0.05 * height;
    lf.lfWeight = FW_BOLD;
    HFONT hFont = CreateFontIndirect(&lf);

    SelectObject(hdc, hFont);
    SetTextColor(hdc, 0x70cc90);
    SetTextAlign(hdc, TA_CENTER);
    TextOut(hdc, width * 0.8, 10, tchar, size);
    return;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static double t;
 
    switch (message)
    {
    case WM_CREATE:
    {
        SetTimer(hWnd, 1, 125, NULL);
        break;
    }
    case WM_TIMER: 
    {
        t += TimeD;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        PaintAxis(hWnd, hdc, ps);
        PaintGraph (hWnd, hdc, ps, t);
        TextCoords(hWnd, hdc, ps, t);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY: 
    {
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    }
    default: return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// Message handler for about box.
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
