// GameOfLife.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "GameOfLife.h"
#include <vector>
#include <exception>

#define MAX_LOADSTRING 100
#define ID_TIMER1 0

enum STATE {
    DEAD,
    OLD,
    NEW
};
class State
{
    int _isAlive;

public: 
    State(int isAlive)
    {
        _isAlive = isAlive;
    }

    int IsAlive()
    {
        return _isAlive;
    }

    void SetIsAlive(int isAlive)
    {
        _isAlive = isAlive;
    }
};

class Cell
{
    State _state = State(DEAD);

public:
    Cell(State state)
    {
        _state = state;
    }

    Cell()
    {

    }

    int IsAlive()
    {
        return _state.IsAlive();
    }

    void SetIsAlive(int isAlive)
    {
        _state.SetIsAlive(isAlive);
    }
};

class Grid
{
    std::vector<std::vector<Cell>> _cells;
    int _width;
    int _height;

public:
    Grid(int width, int height) : _width(width), _height(height)
    {
        _cells.resize(height);

        for (auto rowIndex = 0; rowIndex < height; ++rowIndex)
        {
            _cells[rowIndex].resize(width);
        }
    }

    int GetWidth()
    {
        return _width;
    }

    int GetHeight()
    {
        return _height;
    }

    Cell& GetCell(int rowIndex, int columnIndex)
    {
        if (rowIndex < 0 || rowIndex >= _height) throw std::exception("Wrong rowIndex");
        if (columnIndex < 0 || columnIndex >= _width) throw std::exception("Wrong columnIndex");

        return _cells[rowIndex][columnIndex];
    }
};

class LifeEngine
{
public:
    Grid CalculateNext(Grid currentGrid)
    {
        auto newGrid = Grid(currentGrid.GetWidth(), currentGrid.GetHeight());

        auto distance = 1;

        for (auto rowIndex = 0; rowIndex < currentGrid.GetHeight(); ++rowIndex)
        {
            for (auto columnIndex = 0; columnIndex < currentGrid.GetWidth(); ++columnIndex)
            {
                auto aliveCellCount = CalculateAliveNeighbour(rowIndex, columnIndex, currentGrid, distance);

                if (aliveCellCount == 3 && currentGrid.GetCell(rowIndex, columnIndex).IsAlive() == DEAD)
                {
                    newGrid.GetCell(rowIndex, columnIndex).SetIsAlive(NEW);
                }
                else if ((aliveCellCount == 2 || aliveCellCount == 3) && currentGrid.GetCell(rowIndex, columnIndex).IsAlive() != DEAD)
                {
                    newGrid.GetCell(rowIndex, columnIndex).SetIsAlive(currentGrid.GetCell(rowIndex, columnIndex).IsAlive());
                }
                else
                {
                    newGrid.GetCell(rowIndex, columnIndex).SetIsAlive(currentGrid.GetCell(rowIndex, columnIndex).IsAlive() - 1);
                }
            }
        }

        return newGrid;
    }
    Grid UpdateGrid(Grid grid, int n, int m) {
        Grid newGrid = Grid(n, m);
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                if (j < grid.GetWidth() && i < grid.GetHeight()) {
                    newGrid.GetCell(i, j).SetIsAlive(grid.GetCell(i, j).IsAlive());
                }
                else {
                    newGrid.GetCell(i, j).SetIsAlive(DEAD);
                }
            }
        }
        return newGrid;
    }
private:
    int GetLeftStartIndex(int columnIndex, int distance, Grid currentGrid)
    {
        if (columnIndex - distance < 0) {
            return (currentGrid.GetWidth() - 1 - distance);
        }
        return columnIndex - distance;
    }

    int GetTopStartIndex(int rowIndex, int distance, Grid currentGrid)
    {
        return max(rowIndex - distance, 0);
    }

    int GetRightStartIndex(int columnIndex, int gridWidth, int distance, Grid currentGrid)
    {
        if (columnIndex + distance > gridWidth - 1) {
            return distance;
        }
        return columnIndex + distance;
    }

    int GetBottomStartIndex(int rowIndex, int gridHeight, int distance, Grid currentGrid)
    {
        return min(rowIndex + distance, gridHeight - 1);
    }

    int CalculateAliveNeighbour(int rowIndex, int columnIndex, Grid currentGrid, int distance)
    {
        auto aliveCellCount = 0;

        auto leftStartIndex = GetLeftStartIndex(columnIndex, distance, currentGrid);
        auto rightStartIndex = GetRightStartIndex(columnIndex, currentGrid.GetWidth(), distance, currentGrid);
        auto topStartIndex = GetTopStartIndex(rowIndex, distance, currentGrid);
        auto bottomStartIndex = GetBottomStartIndex(rowIndex, currentGrid.GetHeight(), distance, currentGrid);

        for (auto neighbourColumnIndex = leftStartIndex; neighbourColumnIndex <= rightStartIndex; ++neighbourColumnIndex)
        {
            for (auto neighbourRowIndex = topStartIndex; neighbourRowIndex <= bottomStartIndex; ++neighbourRowIndex)
            {
                if (rowIndex == neighbourRowIndex && columnIndex == neighbourColumnIndex) continue;

                if (currentGrid.GetCell(neighbourRowIndex, neighbourColumnIndex).IsAlive()!=DEAD)
                {
                    ++aliveCellCount;
                }
            }
        }

        return aliveCellCount;
    }
};

Grid grid = Grid(10, 10);
LifeEngine lifeEngine;

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
    LoadStringW(hInstance, IDC_GAMEOFLIFE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEOFLIFE));

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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEOFLIFE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAMEOFLIFE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
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

void DrawLight(HWND hWnd, HDC hdc, int i, int j)
{
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    auto cellWidth = clientRect.right / grid.GetWidth();
    auto cellHeight = clientRect.bottom / grid.GetHeight();

    auto brush = CreateSolidBrush(0x00ddee);
    auto oldBrush = SelectObject(hdc, brush);
    Rectangle(hdc, j * cellWidth, i * cellHeight, (j + 1) * cellWidth, (i + 1) * cellHeight);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
}

void DrawGrid(HWND hWnd, HDC hdc)
{
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    auto cellWidth = clientRect.right / grid.GetWidth();

    for (auto j = 0; j < grid.GetWidth() + 1; ++j)
    {
        MoveToEx(hdc, cellWidth * j, 0, nullptr);
        LineTo(hdc, cellWidth * j, clientRect.bottom);
    }

    auto cellHeight = clientRect.bottom / grid.GetHeight();

    for (auto i = 0; i < grid.GetHeight() + 1; ++i)
    {
        MoveToEx(hdc, 0, cellHeight * i, nullptr);
        LineTo(hdc, clientRect.right, cellHeight * i);
    }
}

void DrawCells(HWND hWnd, HDC hdc)
{
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    auto cellWidth = clientRect.right / grid.GetWidth();
    auto cellHeight = clientRect.bottom / grid.GetHeight();



    for (auto i = 0; i < grid.GetHeight(); ++i)
    {
        for (auto j = 0; j < grid.GetWidth(); ++j)
        {
            switch (grid.GetCell(i, j).IsAlive())
            {
            case NEW: 
            {
                auto brush = CreateSolidBrush(RGB(40, 250, 19));
                auto oldBrush = SelectObject(hdc, brush);
                Ellipse(hdc, j * cellWidth, i * cellHeight, (j + 1) * cellWidth, (i + 1) * cellHeight);
                SelectObject(hdc, oldBrush);
                DeleteObject(brush);
            }
            break;
            case OLD:
            {
                auto brush = CreateSolidBrush(RGB(0, 0, 0));
                auto oldBrush = SelectObject(hdc, brush);
                Ellipse(hdc, j * cellWidth, i * cellHeight, (j + 1) * cellWidth, (i + 1) * cellHeight);
                SelectObject(hdc, oldBrush);
                DeleteObject(brush);
            }
            break;
            }
        }
    }
}


int GetGridCol(HWND hWnd, Grid grid, int x) {
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    auto cellWidth = clientRect.right / grid.GetWidth();

    for (auto j = 0; j < grid.GetWidth() + 1; ++j)
    {
        if (x < ((j + 1) * cellWidth) && x >(j * cellWidth))
            return j;
    }
};

int GetGridRow(HWND hWnd, Grid grid, int x) {
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    auto cellHeight = clientRect.bottom / grid.GetHeight();

    for (auto i = 0; i < grid.GetHeight() + 1; ++i)
    {
        if (x < ((i + 1) * cellHeight) && x >(i * cellHeight))
            return i;
    }
}

bool IsValidSize(int x, int Delta) {
    return (x + Delta) > 2 && (x + Delta) < 26;
}

bool TimerIsAlive;
int tdelta = 3000;
bool CtrlDown = false;
bool ShiftDown = false;
int rowM=0, colM=0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        grid.GetCell(0, 1).SetIsAlive(NEW);
        grid.GetCell(1, 2).SetIsAlive(NEW);
        grid.GetCell(2, 0).SetIsAlive(NEW);
        grid.GetCell(2, 1).SetIsAlive(NEW);
        grid.GetCell(2, 2).SetIsAlive(NEW);

        SetTimer(hWnd, ID_TIMER1, tdelta, nullptr);
        TimerIsAlive = true;
    }
        break;

    case WM_TIMER:
    {
        grid = lifeEngine.CalculateNext(grid);
        InvalidateRect(hWnd, nullptr, true);
    }
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
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

        DrawLight(hWnd, hdc, rowM, colM);
        DrawGrid(hWnd, hdc);
        DrawCells(hWnd, hdc);

        EndPaint(hWnd, &ps);
    }
        break;
    case WM_LBUTTONDOWN:
    {
        auto x = LOWORD(lParam);
        auto y = HIWORD(lParam);
        auto col = GetGridCol(hWnd, grid, x);
        auto row = GetGridRow(hWnd, grid, y);
        grid.GetCell(row, col).SetIsAlive(NEW);
        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_RBUTTONDOWN:
    {
        auto x = LOWORD(lParam);
        auto y = HIWORD(lParam);
        auto col = GetGridCol(hWnd, grid, x);
        auto row = GetGridRow(hWnd, grid, y);
        grid.GetCell(row, col).SetIsAlive(DEAD);
        InvalidateRect(hWnd, nullptr, true);
    }
    break;
    case WM_KEYDOWN:
    {
        switch (wParam) {
        case VK_SPACE:
        {
            if (TimerIsAlive) {
                KillTimer(hWnd, ID_TIMER1);
                TimerIsAlive = false;
            }
            else {
                SetTimer(hWnd, ID_TIMER1, tdelta, nullptr);
                TimerIsAlive = true;
            }
        }
        break;
        case VK_F11: 
        {
            if (!TimerIsAlive) {
                if (!CtrlDown) {
                    grid = lifeEngine.CalculateNext(grid);
                    InvalidateRect(hWnd, nullptr, true);
                }
                else {
                    for (auto i = 0; i < 5; ++i) {
                        grid = lifeEngine.CalculateNext(grid);
                        InvalidateRect(hWnd, nullptr, true);
                    }
                }
            }
        }
        break;
        case VK_CONTROL:
        {
            CtrlDown = true;
        }
        break;
        case VK_SHIFT:
        {
            ShiftDown = true;
        }
        break;
        }
    }
    break;
    case WM_KEYUP:
    {
        switch (wParam) 
        {
        case VK_CONTROL:
        {
            CtrlDown = false;
        }
        break;
        case VK_SHIFT:
        {
            ShiftDown = false;
        }
        break;
        }
    }
    break;
    case WM_MOUSEMOVE:
    {
        auto x = LOWORD(lParam);		auto y = HIWORD(lParam);
        colM = GetGridCol(hWnd, grid, x);
        rowM = GetGridRow(hWnd, grid, y);
        InvalidateRect(hWnd, nullptr, 0);
    }
    break;
    case WM_MOUSEWHEEL:
    {
        int mDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        int Delta = mDelta / 120;
        if (ShiftDown) {
            if (IsValidSize(grid.GetWidth(), Delta)) {
                grid = lifeEngine.UpdateGrid(grid, grid.GetWidth() + Delta, grid.GetHeight());
            }
            else {
                MessageBox(hWnd, L"Invalid size", L"Error", MB_OK | MB_ICONERROR);
            }
        }
        else {
            if (IsValidSize(grid.GetHeight(), Delta)) {
                grid = lifeEngine.UpdateGrid(grid, grid.GetWidth(), grid.GetHeight() + Delta);
            }
            else {
                MessageBox(hWnd, L"Invalid size", L"Error", MB_OK | MB_ICONERROR);
            }
        }
        InvalidateRect(hWnd, nullptr, 0);
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
