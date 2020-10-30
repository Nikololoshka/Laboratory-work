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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // обработка сообщений
    switch (message) {
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
/*
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    int x, y;
    static int sx, sy;

    // обработка сообщений
    switch (message) {
        // определение размеров
        case WM_SIZE: {
            sx = LOWORD(lParam);
            sy = HIWORD(lParam);
            break;
        }
        // отрисовка
        case WM_PAINT: {
            hdc = BeginPaint(hWnd, &ps);
            for (x = 0; x < sx; x += sx / 10) {
                MoveToEx(hdc, x, 0, NULL);
                LineTo(hdc, x, sy);
            }

            for (y = 0; y < sy; y += sy / 10) {
                MoveToEx(hdc, 0, y, NULL);
                LineTo(hdc, sx, y);
            }
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
    HBRUSH brushMain = CreateSolidBrush(RGB(144, 255, 0));
    HBRUSH brushWheels = CreateSolidBrush(RGB(120, 120, 120));

    HDC hdc;
    static int sx, sy;

    // обработка сообщений
    switch (message) {
        // определение размеров
        case WM_SIZE: {
            sx = LOWORD(lParam);
            sy = HIWORD(lParam);
            break;
        }
        // отрисовка
        case WM_PAINT: {
            hdc = BeginPaint(hWnd, &ps);

            int centerX = sx / 2;
            int centerY = sy / 2;

            int rectHeight = (int) sx * 0.1;
            int rectWidth = (int) sy * 0.8;

            SelectObject(hdc, brushMain);

            // корпус
            Rectangle(hdc,
                      centerX - rectWidth / 2,
                      centerY - rectHeight / 2,
                      centerX + rectWidth / 2,
                      centerY + rectHeight / 2);

            // колеса
            int radius = (int) rectWidth / 8;
            SelectObject(hdc, brushWheels);

            // первое
            Ellipse(hdc,
                    centerX - rectWidth / 2 + radius,
                    centerY + rectHeight / 2,
                    centerX - rectWidth / 2 + 3 * radius,
                    centerY + rectHeight / 2 + 2 * radius);

            // второе
            Ellipse(hdc,
                    centerX + rectWidth / 2 - 3 * radius,
                    centerY + rectHeight / 2,
                    centerX + rectWidth / 2 - radius,
                    centerY + rectHeight / 2 + 2 * radius);

            // вверх
            int partHor = (int) rectWidth / 8;
            int partVer = (int) rectHeight * 0.75;

            MoveToEx(hdc, centerX - rectWidth / 2 + 1 * partHor,
                     centerY - rectHeight / 2, NULL);
            LineTo(hdc, centerX - rectWidth / 2 + 3 * partHor
                   , centerY - rectHeight / 2 - partVer);

            MoveToEx(hdc,
                     centerX - rectWidth / 2 + 3 * partHor,
                     centerY - rectHeight / 2 - partVer,
                     NULL);
            LineTo(hdc, centerX - rectWidth / 2 + 6.5 * partHor,
                   centerY - rectHeight / 2 - partVer);

            MoveToEx(hdc,
                     centerX - rectWidth / 2 + 6.5 * partHor,
                     centerY - rectHeight / 2 - partVer,
                     NULL);
            LineTo(hdc, centerX - rectWidth / 2 + 7 * partHor,
                   centerY - rectHeight / 2);

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
