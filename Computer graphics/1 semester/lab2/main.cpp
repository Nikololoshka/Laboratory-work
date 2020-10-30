#include <iostream>
#include <tchar.h>
#include <windows.h>

#define _USE_MATH_DEFINES "123"
#include <math.h>

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
    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

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
    PAINTSTRUCT ps;
    HDC hdc;
    static int sx, sy;
    static HPEN hpen1, hpen2;
    int a, b, x_scr, y_scr; // экранные коорд.
    double x, h;			// физический коорд.

    // обработка сообщений
    switch(message) {
        case WM_CREATE: {
            hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
            hpen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
            break;
        }
        // определение размеров
        case WM_SIZE: {
            sx = LOWORD(lParam);
            sy = HIWORD(lParam);

            break;
        }
        // отрисовка
        case WM_PAINT: {
            hdc = BeginPaint(hWnd, &ps);

            a = sx / 2;
            b = sy / 2;

            SelectObject(hdc, hpen1); // Синее перо

            MoveToEx(hdc, 0, b, NULL);
            LineTo(hdc, sx, b);

            MoveToEx(hdc, a, 0, NULL);
            LineTo(hdc, a, sy);

            MoveToEx(hdc, 0, b, NULL);

            SelectObject(hdc, hpen2);

            h = 3 * M_PI / a;
            for (x = -M_PI, x_scr = 0; x < M_PI; x += h) {
                x_scr = (x + M_PI) * a / M_PI;
                y_scr = b - b * sin(x);
                LineTo(hdc, x_scr, y_scr);
            }

            EndPaint(hWnd, &ps);
            break;
        }
        // разрушение окна
        case WM_DESTROY: {
            DeleteObject(hpen1);
            DeleteObject(hpen2);
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    static int sx, sy;
    static HPEN hpen1, hpen2;
    int a, b, x_scr, y_scr; // экранные коорд.
    double x, h;			// физический коорд.

    // обработка сообщений
    switch(message) {
        case WM_CREATE: {
            hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
            hpen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
            break;
        }
        // определение размеров
        case WM_SIZE: {
            sx = LOWORD(lParam);
            sy = HIWORD(lParam);

            break;
        }
        // отрисовка
        case WM_PAINT: {
            hdc = BeginPaint(hWnd, &ps);

            a = sx / 2;
            b = sy / 2;

            SelectObject(hdc, hpen1); // Синее перо

            MoveToEx(hdc, 0, b, NULL);
            LineTo(hdc, sx, b);

            MoveToEx(hdc, a, 0, NULL);
            LineTo(hdc, a, sy);

            MoveToEx(hdc, 0, b, NULL);

            SelectObject(hdc, hpen2);

            h = 0.1;
            int score = 5;
            for (x = -score, x_scr = 0; x < score; x += h) {

                x_scr = (x + score) * a / score;
                y_scr = b - pow(x, 2) * b / score;

                LineTo(hdc, x_scr, y_scr);
            }

            EndPaint(hWnd, &ps);
            break;
        }
        // разрушение окна
        case WM_DESTROY: {
            DeleteObject(hpen1);
            DeleteObject(hpen2);
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
static int sx, sy;
static HPEN hpen, hpen1, hpen2;   //Тип структуры пера
int a, b, n, x_scr, y_scr, z_src; //Экранные координаты
double x, y, z,                   //Физические координаты объекта
    x_min, x_max, y_min, y_max,   //физические габариты объекта
    Kx, Ky;                       //Коэффициенты масштабирования

//Обработчик сообщений
switch (message) {
    case WM_CREATE: {
        hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
        hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
        hpen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        break;
    }
    // определение размеров
    case WM_SIZE: {
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);

        break;
    }
    case WM_PAINT: {
        hdc = BeginPaint(hWnd, &ps);

        a = sx / 2;
        b = sy / 2;

        SelectObject(hdc, hpen1); // Синее перо

        MoveToEx(hdc, 0, b, NULL);
        LineTo(hdc, sx, b);

        MoveToEx(hdc, a, 0, NULL);
        LineTo(hdc, a, sy);

        MoveToEx(hdc, 0, b, NULL);

        SelectObject(hdc, hpen2);

        // Задание области положения функции
        x_min = -100;
        x_max = 100;
        y_min = -100;
        y_max = 100;
        //Расчёт коэфициентов масштабирования
        Kx = (sx - 220) / (x_max - x_min);
        Ky = (sy - 220) / (y_max - y_min);

        SelectObject(hdc, hpen);   //Синее перо
        MoveToEx(hdc, 0, b, NULL); //отрисовка оси Ох
        LineTo(hdc, sx, b);
        MoveToEx(hdc, a, 0, NULL); //отрисовка оси Оz
        LineTo(hdc, a, sy);

        MoveToEx(hdc, 20, sy - 20, NULL); //отрисовка оси Оy

        LineTo(hdc, sx - 20, 20);

        n = y_max - y_min; //максимальное поле по оси Оу

        //Цикл смещения сечений вдоль оси Оу
        for (y = y_min; y < y_max; y += 5) {
            //закраска красным оттенком сечения поверхности
            hpen1 = CreatePen(PS_SOLID,
                              2,
                              RGB(255, 255 - 255. / n * (y + y_min), 255 - 255. / n * (y + y_min)));
            SelectObject(hdc, hpen1);

            //Определение значения функции в начальной точке сечения
            z = b - 100 * sin(M_PI / 50 * sqrt(x_min * x_min + y * y));
            MoveToEx(hdc, x_min * Kx + a + y, (z + y), NULL);

            //Отрисовка сечения вдоль оси Ох
            for (x = x_min; x < x_max; x += 5) {
                z = b - 100 * sin(M_PI / 50 * sqrt(x * x + y * y));
                LineTo(hdc, x * Kx + a + y, z + y);
            }
        }

        EndPaint(hWnd, &ps);
        break;
    }
    // разрушение окна
    case WM_DESTROY: {
        DeleteObject(hpen1);
        DeleteObject(hpen2);
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
PAINTSTRUCT ps;
HDC hdc;
static int sx, sy;
static HPEN hpen1, hpen2;
double a, b, x_scr, y_scr; // экранные коорд.
double x, h;               // физический коорд.

// обработка сообщений
switch (message) {
    case WM_CREATE: {
        hpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
        hpen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        break;
    }
    // определение размеров
    case WM_SIZE: {
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);

        break;
    }
    // отрисовка
    case WM_PAINT: {
        hdc = BeginPaint(hWnd, &ps);

        a = sx / 2;
        b = sy / 2;

        SelectObject(hdc, hpen1); // Синее перо

        MoveToEx(hdc, 0, b, NULL);
        LineTo(hdc, sx, b);

        MoveToEx(hdc, a, 0, NULL);
        LineTo(hdc, a, sy);

        MoveToEx(hdc, a, b, NULL);

        SelectObject(hdc, hpen2);

        h = 0.05;
        int score = 3;
        for (x = 0, x_scr = 0; x < score; x += h) {
            x_scr = (x + score) * a / score;
            y_scr = b - pow(x, 0.5) * b / score;

            LineTo(hdc, x_scr, y_scr);
        }

        EndPaint(hWnd, &ps);
        break;
    }
    // разрушение окна
    case WM_DESTROY: {
        DeleteObject(hpen1);
        DeleteObject(hpen2);
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

