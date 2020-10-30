#define _USE_MATH_DEFINES "Anime boy"
#include <math.h>
#include <tchar.h>
#include <windows.h>
#include <fstream>
#include "stdio.h"

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
    Задание 1: Изобразить на экране вращающийся при помощи мыши куб с
    удалёнными гранями и закраской (рис. ), применив фрагменты кода:
*/

//---------------------------------------------------------------------------
/*
const int WIDTH = 400;
const int HEIGHT = 300;
float v11, v12, v13, v21, v22, v23, v31, v32, v33, v43;
float rho = 300., thetta = 75., phi = 30., ScreenDist = 500.;
float A, B, C, D, An, Bn, Cn;
float xt[3], yt[3], zt[3];
float Al, Bl, Cl;
float alpha;
float th, ph, costh, cosph, sinth, sinph;
float factor = atan(1.0) / 45.;

class TFPoint
{
public:
    float X;
    float Y;
    float Z;
};

//Задаём координаты точек куба
TFPoint CubePoints[] = {{-50, -50, -50},
                        {50, -50, -50},
                        {50, 50, -50},
                        {-50, 50, -50},
                        {-50, 50, 50},
                        {-50, -50, 50},
                        {50, -50, 50},
                        {50, 50, 50}};
int Gran[6][4] = {{0, 3, 4, 5}, {0, 5, 6, 1}, {2, 7, 4, 3},
                  {7, 6, 5, 4}, {0, 1, 2, 3}, {2, 1, 6, 7}};

void VidMatCoeff(float rho, float thetta, float phi)
{
    //Определение компонентов направления наблюдения для сведения с
    // лучом освещения
    th = thetta * factor;
    ph = phi * factor;
    costh = cos(th);
    sinth = sin(th);
    cosph = cos(ph);
    sinph = sin(ph);
    // Элементы матрицы V
    v11 = -sinth;
    v12 = -cosph * costh;
    v13 = -sinph * costh;
    v21 = costh;
    v22 = -cosph * sinth;
    v23 = -sinph * sinth;
    v31 = 0.;
    v32 = sinph;
    v33 = -cosph;
    v43 = rho;
}

POINT Perspective(float x, float y, float z)
{
    POINT point;
    float xe, ye, ze;
    VidMatCoeff(rho, thetta, phi);
    xe = v11 * x + v21 * y;
    ye = v12 * x + v22 * y + v32 * z;
    ze = v13 * x + v23 * y + v33 * z + v43;
    // Экранные координаты
    point.x = ScreenDist * xe / ze + 400.;
    point.y = ScreenDist * ye / ze + 300.;
    return point;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    PAINTSTRUCT ps;
    static HBRUSH hBrush;

    POINT point1[4];
    HDC hdc;
    int sx, sy, xPos, yPos, zDelta;

    // обработка сообщений
    switch (message) {
        case WM_MOUSEMOVE: {
            sx = LOWORD(lParam); //координата мыши по оси Х
            sy = HIWORD(lParam); //координата мыши по оси У
            thetta += ((sx % 180) - 90) / 10;
            phi += ((sy % 180) - 90) / 10;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case WM_MOUSEWHEEL: {
            zDelta = (int) wParam; // wheel rotation
            ScreenDist -= zDelta / 1000000.;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        // отрисовка
        case WM_PAINT: {
            hdc = BeginPaint(hWnd, &ps);
            th = thetta * factor;
            ph = phi * factor;
            costh = cos(th);
            sinth = sin(th);
            cosph = cos(ph);
            sinph = sin(ph);
            A = rho * sinph * costh;
            B = rho * sinph * sinth;
            C = rho * cosph;
            Al = A / (sqrt(A * A + B * B + C * C));
            Bl = B / (sqrt(A * A + B * B + C * C));
            Cl = C / (sqrt(A * A + B * B + C * C));
            for (int i = 0; i < 6; i++) { //
                for (int j = 0; j < 3; j++) {
                    xt[j] = CubePoints[Gran[i][j]].X;
                    yt[j] = CubePoints[Gran[i][j]].Y;
                    zt[j] = CubePoints[Gran[i][j]].Z;
                }
                //
                A = yt[0] * (zt[1] - zt[2]) - yt[1] * (zt[0] - zt[2]) + yt[2] * (zt[0] - zt[1]);
                B = -(xt[0] * (zt[1] - zt[2]) - xt[1] * (zt[0] - zt[2]) + xt[2] * (zt[0] - zt[1]));
                C = xt[0] * (yt[1] - yt[2]) - xt[1] * (yt[0] - yt[2]) + xt[2] * (yt[0] - yt[1]);

                An = A / (sqrt(A * A + B * B + C * C));
                Bn = B / (sqrt(A * A + B * B + C * C));
                Cn = C / (sqrt(A * A + B * B + C * C));

                alpha = (An * Al + Bn * Bl + Cn * Cl);
                for (int j=0; j<4; j++)
                {
                    point1[j] = Perspective(CubePoints[Gran[i][j]].X,
                                            CubePoints[Gran[i][j]].Y,
                                            CubePoints[Gran[i][j]].Z);
                }
                //Определение направления обхода точек грани для выявления ориентации к
                // наблюдателю
                D = point1[0].x * (point1[1].y - point1[2].y)
                    - point1[1].x * (point1[0].y - point1[2].y)
                    + point1[2].x * (point1[0].y - point1[1].y);
                if (D < 0) {
                    hBrush = CreateSolidBrush(
                        RGB((1 - alpha) * 255, (1 - alpha) * 255, (1 - alpha) * 255));
                    SelectObject(hdc, hBrush);
                    Polygon(hdc, point1, 4);
                }
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
/*
    Задание 2: С помощью фрагментов представленного кода на основе приложения
    «Каркас» построить приложение «Кривая Безье» (Рис.10):

    а) Организуйте новый проект с названием «Безье».

    б) Создайте текстовый файл dat.txt и поместите в папку “Debug”:
    211 227
    65 593
    270 851
    437 276
    521 79
    563 694
    743 808
    917 858
    947 449
    746 179

    в) Постройте и скомпилируйте приложение из фрагментов кода:
*/
/*
static int sx, sy;
const int SCALE = 1000; //размер логического окна
const int MARK = 4; //размер прямоугольного маркера точек

void DcInLp(POINT &point)
{
    point.x = point.x * SCALE / sx;
    point.y = SCALE - point.y * SCALE / sy;
}

void transform(HDC &hdc)
{
    SetMapMode(hdc, MM_ANISOTROPIC); //Устанавливаем локальную систему
    SetWindowExtEx(hdc, SCALE, -SCALE, NULL); //координат 1000х1000 с центром в
    SetViewportExtEx(hdc, sx, sy, NULL);      //левом нижнем углу
    SetViewportOrgEx(hdc, 0, sy, NULL);       //
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    PAINTSTRUCT ps;
    static HBRUSH hBrush;
    HDC hdc;

    static HPEN hDash, hBezier; // два пера
    static HBRUSH hRect, hSel; // две кисти
    static POINT pt[20]; // массив хранения плоских точек
    static POINT point; // структура под одну плоскую точку
    RECT rt; // структура точек прямоугольника
    static int count, index; // счётчик точек,
    static bool capture; // логическая переменная для мыши
    int i;
    std::ifstream in; //класс файлового потокового ввода-вывода
    std::ofstream out;

    // обработка сообщений
    switch (message) {
    case WM_CREATE: {
            in.open("./dat.txt"); // открытие файлового потока
            if (in.fail()) {
                MessageBox(hWnd,
                           _T("Файл dat.txt не найден"),
                           _T("Открытие файла"),
                           MB_OK | MB_ICONEXCLAMATION);
                PostQuitMessage(0);
                return 1;
            }
            // пока запоняется координата x - заполняем y
            // в переменной count накапливается размер массива точек
            for (count = 0; in >> pt[count].x; count++) {
                in >> pt[count].y;
            }
            in.close(); // закрытие файлового потока
            hDash = CreatePen(PS_DASH, 1, 0);
            hBezier = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
            hRect = CreateSolidBrush(RGB(128, 0, 128));
            hSel = CreateSolidBrush(RGB(255, 0, 0));
            break;
        }
        case WM_SIZE: {
            sx = LOWORD(lParam);
            sy = HIWORD(lParam);
            break;
        }
        case WM_LBUTTONDOWN: {
            point.x = LOWORD(lParam);
            point.y = HIWORD(lParam);
            //Преобразование экранных координат мыши в логические
            DcInLp(point);
            for (i = 0; i <= count; i++) {
                SetRect(&rt, pt[i].x - MARK, pt[i].y - MARK, pt[i].x + MARK, pt[i].y + MARK);
                if (PtInRect(&rt, point)) { // Курсор мыши попал в точку
                    index = i;
                    capture = true;
                    hdc = GetDC(hWnd);
                    transform(hdc); //Переход в логические координаты
                    FillRect(hdc, &rt, hSel); //Отметим прямоугольник цветом
                    ReleaseDC(hWnd, hdc);
                    SetCapture(hWnd);
                    return 0;
                }
            }
            break;
        }
        case WM_LBUTTONUP: {
            if (capture) {
                ReleaseCapture(); //Освобождение мыши
                capture = false;
            }
            break;
        }
        case WM_MOUSEMOVE: {
            if (capture) { //Мышь захвачена
                point.x = LOWORD(lParam);
                point.y = HIWORD(lParam);
                DcInLp(point); //Преобразование экранных координат мыши
                pt[index] = point; // в логические координаты
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }
        // отрисовка
        case WM_PAINT: {
            hdc = BeginPaint(hWnd, &ps);
            transform(hdc); //Переход в логические координаты
            SelectObject(hdc, hDash);
            Polyline(hdc, pt, count); //Строим ломанную линию
            SelectObject(hdc, hBezier);
            PolyBezier(hdc, pt, count); //Строим кривую Безье
            for (i = 0; i < count; i++) { //Закрашиваем точки графика прямоугольниками
                SetRect(&rt, pt[i].x - MARK, pt[i].y - MARK, pt[i].x + MARK, pt[i].y + MARK);
                FillRect(hdc, &rt, hRect);
            }
            EndPaint(hWnd, &ps);
            break;
        }
            // разрушение окна
        case WM_DESTROY: {
            DeleteObject(hDash);
            DeleteObject(hBezier);
            DeleteObject(hRect);
            DeleteObject(hSel);
            out.open("dat.txt"); //открыть файловый поток для записи даннах
            for (i = 0; i < count; i++) {
                out << pt[i].x << '\t' << pt[i].y << '\n';
            }
            out.close();

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
    Задание 3: По примеру кода «Безье» адаптировать код программы, написанной в
    MS-DOS для построения кривой В-сплайна:
*/

static int sx, sy;
const int SCALE = 1000; // размер логического окна
const int MARK = 4;     // размер прямоугольного маркера точек
const int N = 30;       // кол-во точек в B-сплайне

void DcInLp(POINT &point)
{
    point.x = point.x * SCALE / sx;
    point.y = SCALE - point.y * SCALE / sy;
}

void transform(HDC &hdc)
{
    SetMapMode(hdc, MM_ANISOTROPIC); //Устанавливаем локальную систему
    SetWindowExtEx(hdc, SCALE, -SCALE, NULL); //координат 1000х1000 с центром в
    SetViewportExtEx(hdc, sx, sy, NULL);      //левом нижнем углу
    SetViewportOrgEx(hdc, 0, sy, NULL);       //
}

void transformToBSplayn(HDC hdc, POINT pt[], int count)
/*
 *  Функция для отрисовки B-сплайна.
*/
{
    float eps = 0.04f, t, X, Y;
    float xA, xB, xC, xD, yA, yB, yC, yD;
    float a0, a1, a2, a3, b0, b1, b2, b3;
    int i, j, first;

    for (i = 0; i <= count; i++) {
        MoveToEx(hdc, pt[i].x - eps, pt[i].y - eps, NULL);
        LineTo(hdc, pt[i].x + eps, pt[i].y + eps);
        MoveToEx(hdc, pt[i].x + eps, pt[i].y + eps, NULL);
        LineTo(hdc, pt[i].x - eps, pt[i].y - eps);
    }
    first = 1;
    for (i = 1; i < count - 1; i++) {
        xA = pt[i - 1].x;
        xB = pt[i].x;
        xC = pt[i + 1].x;
        xD = pt[i + 2].x;
        yA = pt[i - 1].y;
        yB = pt[i].y;
        yC = pt[i + 1].y;
        yD = pt[i + 2].y;
        a3 = (-xA + 3 * (xB - xC) + xD) / 6.0;
        b3 = (-yA + 3 * (yB - yC) + yD) / 6.0;
        a2 = (xA - 2 * xB + xC) / 2.0;
        b2 = (yA - 2 * yB + yC) / 2.0;
        a1 = (xC - xA) / 2.0;
        b1 = (yC - yA) / 2.0;
        a0 = (xA + 4 * xB + xC) / 6.0;
        b0 = (yA + 4 * yB + yC) / 6.0;

        for (j = 0; j <= N; j++) {
            t = (float) j / (float) N;
            X = ((a3 * t + a2) * t + a1) * t + a0;
            Y = ((b3 * t + b2) * t + b1) * t + b0;
            if (first) {
                first = 0;
                MoveToEx(hdc, X, Y, NULL);
            } else {
                LineTo(hdc, X, Y);
            }
        }
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    static HBRUSH hBrush;
    HDC hdc;

    static HPEN hDash, hBezier; // два пера
    static HBRUSH hRect, hSel;  // две кисти
    static POINT pt[20];        // массив хранения плоских точек
    static POINT point;         // структура под одну плоскую точку
    RECT rt;                    // структура точек прямоугольника
    static int count, index;    // счётчик точек,
    static bool capture;        // логическая переменная для мыши
    int i;
    std::ifstream in; //класс файлового потокового ввода-вывода
    std::ofstream out;

    // обработка сообщений
    switch (message) {
        case WM_CREATE: {
            in.open("dat.txt"); // открытие файлового потока
            if (in.fail()) {
                MessageBox(hWnd,
                           _T("Файл dat.txt не найден"),
                           _T("Открытие файла"),
                           MB_OK | MB_ICONEXCLAMATION);
                PostQuitMessage(0);
                return 1;
            }
            // пока запоняется координата x - заполняем y
            // в переменной count накапливается размер массива точек
            for (count = 0; in >> pt[count].x; count++) {
                in >> pt[count].y;
            }
            in.close(); // закрытие файлового потока
            hDash = CreatePen(PS_DASH, 1, 0);
            hBezier = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
            hRect = CreateSolidBrush(RGB(128, 0, 128));
            hSel = CreateSolidBrush(RGB(255, 0, 0));
            break;
        }
        case WM_SIZE: {
            sx = LOWORD(lParam);
            sy = HIWORD(lParam);
            break;
        }
        case WM_LBUTTONDOWN: {
            point.x = LOWORD(lParam);
            point.y = HIWORD(lParam);
            //Преобразование экранных координат мыши в логические
            DcInLp(point);
            for (i = 0; i <= count; i++) {
                SetRect(&rt, pt[i].x - MARK, pt[i].y - MARK, pt[i].x + MARK, pt[i].y + MARK);
                if (PtInRect(&rt, point)) { // Курсор мыши попал в точку
                    index = i;
                    capture = true;
                    hdc = GetDC(hWnd);
                    transform(hdc); //Переход в логические координаты
                    FillRect(hdc, &rt, hSel); //Отметим прямоугольник цветом
                    ReleaseDC(hWnd, hdc);
                    SetCapture(hWnd);
                    return 0;
                }
            }
            break;
        }
        case WM_LBUTTONUP: {
            if (capture) {
                ReleaseCapture(); //Освобождение мыши
                capture = false;
            }
            break;
        }
        case WM_MOUSEMOVE: {
            if (capture) { //Мышь захвачена
                point.x = LOWORD(lParam);
                point.y = HIWORD(lParam);
                DcInLp(point); //Преобразование экранных координат мыши
                pt[index] = point; // в логические координаты
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }
        // отрисовка
        case WM_PAINT: {
            hdc = BeginPaint(hWnd, &ps);
            transform(hdc); //Переход в логические координаты
            SelectObject(hdc, hDash);
            Polyline(hdc, pt, count); //Строим ломанную линию
            SelectObject(hdc, hBezier);
            transformToBSplayn(hdc, pt, count);

            for (i = 0; i < count; i++) {
                //Закрашиваем точки графика прямоугольниками
                SetRect(&rt, pt[i].x - MARK, pt[i].y - MARK, pt[i].x + MARK, pt[i].y + MARK);
                FillRect(hdc, &rt, hRect);
            }
            EndPaint(hWnd, &ps);
            break;
        }
            // разрушение окна
        case WM_DESTROY: {
            DeleteObject(hDash);
            DeleteObject(hBezier);
            DeleteObject(hRect);
            DeleteObject(hSel);
            out.open("dat.txt"); //открыть файловый поток для записи даннах
            for (i = 0; i < count; i++) {
                out << pt[i].x << '\t' << pt[i].y << '\n';
            }
            out.close();

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
