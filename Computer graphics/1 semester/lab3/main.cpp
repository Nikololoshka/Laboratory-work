#include <tchar.h>
#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");

int APIENTRY WinMain(HINSTANCE This, HINSTANCE Prev, LPSTR cmd, int mode)
{
    HWND hWnd;   // дескриптор главного окна программы
    MSG msg;     // структурв для хранения сообщений
    WNDCLASS wc; // класс окна

    // определение класса окна
    wc.hInstance = This;
    wc.lpszClassName = WinName; // имя класса окна
    wc.lpfnWndProc = WndProc;   // функция окна

    wc.style = CS_HREDRAW | CS_VREDRAW;         // стиль окна
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // стандартная иконка
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   // стандартный курсор
    wc.lpszMenuName = NULL;                     // нет меню
    wc.cbClsExtra = 0;                          // нет доп. данных класса
    wc.cbWndExtra = 0;                          // нет доп. данных окна

    // белый фон
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // регистрация окна
    if (!RegisterClass(&wc)) {
        return 0;
    }

    // создания окна
    hWnd = CreateWindow(WinName,                         // имя класса окна
                        _T("Каркас Windows-приложения"), // заголовок окна
                        WS_OVERLAPPEDWINDOW,             // стиль окна
                        CW_USEDEFAULT,                   // X
                        CW_USEDEFAULT,                   // Y
                        CW_USEDEFAULT,                   // Width
                        CW_USEDEFAULT,                   // Height
                        HWND_DESKTOP, // Дескриптор родительского окна
                        NULL,
                        This,
                        NULL);

    ShowWindow(hWnd, mode);

    // цикл обработки сообщений
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); // функция транслирования кодов нажатой клавиши
        DispatchMessage(&msg); // посылает сообщение в WndProc()
    }

    return 0;
}

/*
    Оконная функция, вызываемая операционной системой.
    Получает сообщения из очереди для данного приложения
*/
/*
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    POINT pt[5] = {{0, 100}, {-59, -81}, {95, 31}, {-95, 31}, {59, -81}};
    const int WIDTH = 400;
    const int HEIGHT = 300;
    static int sx, sy, i, k;
    static HBRUSH hBrush;

    HDC hdc;

    // обработка сообщений
    switch (message) {
        // определение размеров
        case WM_SIZE: {
            sx = LOWORD(lParam);
            sy = HIWORD(lParam);
            break;
        }
        case WM_CREATE: {
            i = MessageBox(hWnd,
                           _T("Будем рисовать красную звезду?"),
                           _T("Политический вопрос"),
                           MB_YESNO | MB_ICONQUESTION);
            k = (i == IDYES) ? 1 : 0;
            break;
        }
        // отрисовка
        case WM_PAINT: {
            hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Создание кисти
            hdc = BeginPaint(hWnd, &ps);

            // Установка режима
            SetMapMode(hdc, MM_ANISOTROPIC);
            //Установка логических размеров вывода, ось У направлена вверх
            SetWindowExtEx(hdc, WIDTH, -HEIGHT, NULL);

            //Установка физических размеров на окно
            SetViewportExtEx(hdc, sx, sy, NULL);

            //Установка начала координат
            SetViewportOrgEx(hdc, sx / 2, sy / 2, NULL);

            BeginPath(hdc);
            Polyline(hdc, pt, 5);
            CloseFigure(hdc);
            EndPath(hdc);
            SelectObject(hdc, hBrush);
            SetPolyFillMode(hdc, WINDING); //Режим закрашивания "вся фигура"
            FillPath(hdc);

            EndPaint(hWnd, &ps);
            break;
        }
            // разрушение окна
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        // по умолчанию
        default: {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }

    return 0;
}
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
PAINTSTRUCT ps;
POINT pt[3] = {{0, 90}, {-100, -82}, {100, -82}};
const int WIDTH = 400;
const int HEIGHT = 300;
static int sx, sy, i, k;
static HBRUSH hBrush;

HDC hdc;

// обработка сообщений
switch (message) {
    // определение размеров
    case WM_SIZE: {
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        break;
    }
    case WM_CREATE: {
        i = MessageBox(hWnd,
                       _T("Будем рисовать красный равносторонний треугольник?"),
                       _T("Не политический вопрос"),
                       MB_YESNO | MB_ICONQUESTION);
        k = (i == IDYES) ? 1 : 0;
        break;
    }
    // отрисовка
    case WM_PAINT: {
        hdc = BeginPaint(hWnd, &ps);
        // ***************
        // Равносторонний треугольник
        // **************

        hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Создание кисти

        // Установка режима
        SetMapMode(hdc, MM_ANISOTROPIC);
        //Установка логических размеров вывода, ось У направлена вверх
        SetWindowExtEx(hdc, WIDTH, -HEIGHT, NULL);
        //Установка физических размеров на окно
        SetViewportExtEx(hdc, sx, sy, NULL);
        //Установка начала координат
        SetViewportOrgEx(hdc, sx / 2, sy / 2, NULL);

        BeginPath(hdc);
        Polyline(hdc, pt, 3);
        CloseFigure(hdc);
        EndPath(hdc);
        SelectObject(hdc, hBrush);

        SetPolyFillMode(hdc, WINDING); //Режим закрашивания "вся фигура"
        FillPath(hdc);

        EndPaint(hWnd, &ps);
        break;
    }
        // разрушение окна
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    // по умолчанию
    default: {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

    return 0;
}

