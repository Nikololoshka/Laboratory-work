#include <Windows.h>
#include <iostream>
#include <vector>
#include <windowsx.h>

#include "cball.h"
#include "cballsarray.h"
#include "cballsettingsmonitor.h"

// Заголовочный файл определения класса CTrap.
#include "ctrap.h"
#include "ctrapinverted.h"

// Макрос определения клавиши "G".
#define VK_G 0x47

static RECT g_rectWnd;
static CBallsArray balls(50);
static DWORD g_prevFrameTime;
static CBallSettingsMonitor monitor;

static BOOL g_isGrav = FALSE;

// Прототип функции обработки сообщений.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Функция, создающая и регистрирующая класс окна приложения.
BOOL InitAppClass(HINSTANCE& hInstance)
{
    // Идентификатор класса.
    ATOM class_id; // Объект класса окна приложения.
    WNDCLASS wc;
    // Заполнение блока памяти.
    memset(&wc, 0, sizeof(wc));
    // Передача объекту класса окна приложения аттрибутов.
    wc.lpszMenuName = nullptr; // Окно без меню.
    wc.style = CS_HREDRAW | CS_VREDRAW; // Указание о перерисовке окна при изменении его ширины и высоты.
    wc.lpfnWndProc = static_cast<WNDPROC>(WndProc); // Указатель наоконную процедуру.
    wc.cbClsExtra = 0; // Установка числа дополнительных байт, которые размещаются вслед за структурой класса окна, равным 0.
    wc.cbWndExtra = 0; // Установка числа дополнительных байт, которые размещаются вслед за экземпляром окна, равным 0.
    wc.hInstance = hInstance; // Дескриптор экземпляра,который содержит оконную процедуру для класса.
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION); //Дескриптор значка класса.
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW); // Дескриптор курсора класса.
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Дескриптор кисти фона класса.
    wc.lpszClassName = "LabWork1"; // Задание именикласса окна.
    class_id = RegisterClass(&wc); // Регистрация класса.

    // Проверка регистрации класса.
    if (class_id != 0)
        return TRUE;

    return FALSE;
}

// Функция, отвечающая за создание окна.
BOOL InitWindow(HINSTANCE& hInstance, int cmdShow, HWND& mainWnd)
{
    // Создание окна.
    mainWnd = CreateWindow("LabWork1", "Лабораторная работа № 1",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, nullptr, nullptr,
        hInstance, nullptr);

    // Если окно не создано.
    if (!mainWnd)
        return FALSE;

    ShowWindow(mainWnd, cmdShow); // Отобразить окно.
    UpdateWindow(mainWnd); // Обновить окно.

    return TRUE;
}

// Функция для работы в случае отсутствия сообщений в очереди.
void OnIdle(HWND& mainWnd)
{
    DWORD cur_time = GetTickCount();
    DWORD delta_time = cur_time - g_prevFrameTime;

    // Перемещение шариков.
    balls.Move(delta_time);
    g_prevFrameTime = cur_time;

    // Учет влияния гравитации.
    if (g_isGrav)
        balls.SetGravityFactor(1.0);
    else
        balls.SetGravityFactor(0.0);

    InvalidateRect(mainWnd, NULL, TRUE);
}

// Цикл обработки сообщений.
WPARAM StartMessageLoop(HWND& mainWnd)
{
    MSG msg;
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            DispatchMessage(&msg);

        } else {
            Sleep(20);
            OnIdle(mainWnd);
        }
    }
    return msg.wParam;
}

// Точка входа для Windows-приложений:
//      hInstance – идентификатор текущей запущенной копии приложения, присваивается системой;
//      hPrevInstance – оставлен для совместимости с предыдущими версиями, всегда имеет значение NULL;
//      lpCmdLine – строка, переданная в качестве параметров командной строки при запуске приложения;
//      nCmdShow – константа, показывающая как должно быть запущено приложение.
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int cmdShow)
{
    HWND mainWnd;

    // Если класс окна не инициализирован.
    if (!InitAppClass(hInstance))
        return 0;

    // Если окно не создано.
    if (!InitWindow(hInstance, cmdShow, mainWnd))
        return 0;

    // Инициализация параметров объектов класса CBallsArray.
    CBall* ball;
    ball = balls.Add();
    ball->SetParams(10, 10, 5, 50, 50, g_rectWnd);
    ball = balls.Add();
    ball->SetParams(100, 10, 5, -70, -70, g_rectWnd);

    g_prevFrameTime = GetTickCount();

    // Возвращаемое значение.
    return static_cast<int>(StartMessageLoop(mainWnd));
}

// Функция обработки сообщений.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    // Организация действий при получении соощений:
    switch (msg) {
    // Завершение работы.
    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    // Отрисовка.
    case WM_PAINT: {
        HDC hDC;
        PAINTSTRUCT ps;
        // Начало рисования.
        hDC = BeginPaint(hWnd, &ps);

        // Текст о включении или выключении гравитации.
        if (g_isGrav)
            TextOut(hDC, 35, 5, "Гравитация включена", 19);
        else
            TextOut(hDC, 35, 5, "Гравитация выключена", 20);

        // Рисование ловушки.
        balls.trap->Draw(hDC);
        balls.trapInverted->Draw(hDC);

        // Рисование шариков.
        balls.Draw(hDC);
        // Рисование монитора управления направлением и скоростью шаров.
        monitor.Draw(hDC);

        // Конец рисования.
        EndPaint(hWnd, &ps);
        return 0;
    }
    // Изменение зазмеров окна.
    case WM_SIZE: {

        g_rectWnd.top = 0;
        g_rectWnd.left = 0;
        g_rectWnd.bottom = HIWORD(lParam);
        g_rectWnd.right = LOWORD(lParam);

        // Передача измененных границ в класс CBallsArray.
        balls.SetBounds(g_rectWnd);

        return 0;
    }
    // Обработка щелчка мыши (отпускания кнопки мыши).
    case WM_LBUTTONUP: {
        double xpos = GET_X_LPARAM(lParam);
        double ypos = GET_Y_LPARAM(lParam);
        CBall* ball = balls.Add();

        if (ball != NULL) {
            double vx, vy;
            monitor.GetVxVy(vx, vy);
            ball->SetParams(xpos, ypos, 2, vx, vy, g_rectWnd);
        }

        return 0;
    }
    // Обработка щелчка правой кнопки мыши (отпускания кнопки мыши).
    case WM_RBUTTONUP: {
        double xpos = GET_X_LPARAM(lParam);
        double ypos = GET_Y_LPARAM(lParam);
        CColoredBall* ball = balls.AddColoredBall();
        if (ball != NULL) {
            double vx, vy;
            monitor.GetVxVy(vx, vy);
            ball->SetParams(xpos, ypos, 3, vx, vy, g_rectWnd);
            ball->SetColor(255, 0, 0);
        }
        return 0;
    }
    // Обработка щелчка средней кнопки мыши (отпускания кнопки мыши).
    case WM_MBUTTONUP: {
        double xpos = GET_X_LPARAM(lParam);
        double ypos = GET_Y_LPARAM(lParam);

        CBrightBall* ball = balls.AddBrightBall();
        if (ball != NULL) {
            double vx, vy;
            monitor.GetVxVy(vx, vy);
            ball->SetParams(xpos, ypos, 6, vx, vy, g_rectWnd);
            ball->SetColor(0, 0, 0);
        }
        return 0;
    }
    // Обработка нажатия клавиш клавиатуры.
    case WM_KEYDOWN: {
        switch (wParam) {
        // Клавиша "вниз"
        case VK_DOWN:
            monitor.SpeedDown();
            return 0;
        // Клавиша "вверх"
        case VK_UP:
            monitor.SpeedUp();
            return 0;
        // Клавиша "влево"
        case VK_LEFT:
            monitor.AngleUp();
            return 0;
        // Клавиша "вправо"
        case VK_RIGHT:
            monitor.AngleDown();
            return 0;
        // Клавиша "G"
        case VK_G:
            if (g_isGrav) {
                g_isGrav = FALSE;
            } else {
                g_isGrav = TRUE;
            }
            return 0;
        }
    }

    default:
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
