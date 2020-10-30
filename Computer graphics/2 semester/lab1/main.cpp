#include <tchar.h>
#include <vector>
#include <windows.h>
#include <windowsx.h>

#include "cball.h"
#include "chlimiter.h"
#include "crect.h"

static CBall b1(10, 10, 50, 50, 10);
static CHLimiter h1(250, 350, 300);
static std::vector<CRect*> rects;

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
    wc.lpszClassName = L"LabWork1"; // Задание именикласса окна.
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
    mainWnd = CreateWindow(L"LabWork1", L"Лабораторная работа № 1",
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
    DWORD ticks = GetTickCount();
    b1.Move(ticks);
    InvalidateRect(mainWnd, nullptr, TRUE);
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

    // добавление прямоугольников
    rects.push_back(new CRect(100, 110, 50, 50));
    rects.push_back(new CRect(200, 50, 20, 70));
    rects.push_back(new CRect(20, 200, 150, 10));
    rects.push_back(new CRect(50, 300, 120, 50));
    rects.push_back(new CRect(300, 100, 10, 100));

    RECT cr;
    // Вычисление границ окна.
    GetClientRect(mainWnd, &cr);
    // Передача границ окна в метод класса CBall.
    b1.SetBounds(cr);
    // Передача границ препятствия в метод класса CBall.
    b1.SetLimiter(&h1);
    b1.SetRects(rects);

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

        // Рисование шарика.
        b1.Draw(hDC);
        // Рисование препятствия.
        h1.Draw(hDC);
        // Рисование препятствий (прямоугольников).
        for (const auto& rect : rects) {
            rect->Draw(hDC);
        }

        // Конец рисования.
        EndPaint(hWnd, &ps);
        return 0;
    }
    // Изменение зазмеров окна.
    case WM_SIZE: {
        RECT rect;
        rect.top = 0;
        rect.left = 0;
        rect.bottom = HIWORD(lParam);
        rect.right = LOWORD(lParam);
        // Передача измененных границ в класс CBall.
        b1.SetBounds(rect);
        return 0;
    }
    // Обработка нажатия клавиш клавиатуры.
    case WM_KEYDOWN: {
        switch (wParam) {
        case VK_DOWN:
            h1.MoveY(-3);
            return 0;
        case VK_UP:
            h1.MoveY(3);
            return 0;
        case VK_LEFT:
            h1.MoveX(3);
            return 0;
        case VK_RIGHT:
            h1.MoveX(-3);
            return 0;
        }
        break;
    }

    default:
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
