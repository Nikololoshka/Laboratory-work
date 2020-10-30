#include <tchar.h>
#include <windows.h>
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
    PAINTSTRUCT ps;
    HDC hdc;
    static int sx, sy;
    static HPEN hpen;
    int a, b, x_scr, y_scr; //Экранные координаты
    float x[4] = {6.0, 6.0, 5.9, 6.1},
          y[4] = {-0.25, 0.25, 0.0, 0.0}; //Объектные координаты стрелки
    float xMax = 6.5, yMax = 6.5;         //Обеъектные координаты окна
    float Kx, Ky; //Коэффициенты масштабирования объектных
    //координат в экранные

    // обработка сообщений
    switch (message) {
        // определение размеров
        case WM_SIZE: {
            sx = LOWORD(lParam);
            sy = HIWORD(lParam);
            break;
        }
        case WM_CREATE: {
            hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            break;
        }
        // отрисовка
        case WM_PAINT: {
            hdc = BeginPaint(hWnd, &ps); //Начало рисования
            int i, j;
            float pi, phi, cos_phi, sin_phi, xx, yy;
            pi = 4.0 * atan(1.0);
            phi = 6 * pi / 180; //определение угла поворота
            cos_phi = cos(phi);
            sin_phi = sin(phi);      //в радианах
            SelectObject(hdc, hpen); //Синее перо
            Kx = sx / xMax;
            Ky = sy / yMax;
            for (i = 1; i <= 14; i++) //Цикл отрисовки 14 стрелок
            {
                for (j = 0; j <= 3; j++) //Цикл пересчёта координат поворота
                {                        //стрелки
                    xx = x[j];
                    yy = y[j];
                    x[j] = xx * cos_phi - yy * sin_phi;
                    y[j] = xx * sin_phi + yy * cos_phi;
                }
                //Изображение текущей стрелки
                MoveToEx(hdc, x[0] * Kx, sy - y[0] * Ky, NULL); //начало стрелки
                for (j = 1; j <= 3; j++)
                    LineTo(hdc, x[j] * Kx, sy - y[j] * Ky);
                LineTo(hdc, x[1] * Kx, sy - y[1] * Ky); //завершение стрелки
            }
            EndPaint(hWnd, &ps); //завершение рисования
            break;
        }
            // разрушение окна
        case WM_DESTROY: {
            DeleteObject(hpen);
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
static HPEN hpen;

POINT pt[4] = {{-100, 100}, {-100, -100}, {100, -100}, {100, 100}};
POINT pt1[4];
const int WIDTH = 400;
const int HEIGHT = 300;
int n = 8, i, j;
double alpha = M_PI / n;
int sx, sy;
static HBRUSH hBrush;
int a, b, x_scr, y_scr; //Экранные координаты
double x;

// обработка сообщений
switch (message) {
    // определение размеров
    case WM_SIZE: {
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        break;
    }
    case WM_CREATE: {
        hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        break;
    }
    // отрисовка
    case WM_PAINT: {
        hdc = BeginPaint(hWnd, &ps); //Начало рисования
        for (i = 0; i <= n; i++) {
            // Создание изменения цвета кисти
            hBrush = CreateSolidBrush(RGB(255, 255 - 255. / n * i, 255 - 255. / n * i));
            SelectObject(hdc, hBrush);
            for (j = 0; j <= 3; j++) {
                pt1[j].x = 500 + (pt[j].x * cos(alpha * i) - pt[j].y * sin(alpha * i)) + i * 10;
                pt1[j].y = 300 + (pt[j].x * sin(alpha * i) + pt[j].y * cos(alpha * i));
            }
            Polygon(hdc, pt1, 4);
        }
        EndPaint(hWnd, &ps); //завершение рисования
        break;
    }
        // разрушение окна
    case WM_DESTROY: {
        DeleteObject(hpen);
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
HDC hdc;
static HPEN hpen;

POINT pt[3] = {{0, 90}, {-100, -82}, {100, -82}};
POINT pt1[3];
int n = 4, i, j;
double alpha = M_PI / n;
int sx, sy;
static HBRUSH hBrush;

// обработка сообщений
switch (message) {
    // определение размеров
    case WM_SIZE: {
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        break;
    }
    case WM_CREATE: {
        hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        break;
    }
    // отрисовка
    case WM_PAINT: {
        hdc = BeginPaint(hWnd, &ps); //Начало рисования
        for (i = 0; i <= n; i++) {
            // Создание изменения цвета кисти
            hBrush = CreateSolidBrush(RGB(255, 255 - 255. / n * i, 255 - 255. / n * i));
            SelectObject(hdc, hBrush);
            for (j = 0; j < 3; j++) {
                pt1[j].x = (pt[j].x * cos(alpha * i) - pt[j].y * sin(alpha * i)) + i * 250 + 200;
                pt1[j].y = 300 + (pt[j].x * sin(alpha * i) + pt[j].y * cos(alpha * i));
            }
            Polygon(hdc, pt1, 3);
        }
        EndPaint(hWnd, &ps); //завершение рисования
        break;
    }
        // разрушение окна
    case WM_DESTROY: {
        DeleteObject(hpen);
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


