#include "ctrap.h"

// Заголовочный файл определения математических функций.
#include <math.h>

// Конструктор класса CTrap.
CTrap::CTrap(double x, double y, double f, double r)
{
    this->x = x;
    this->y = y;
    this->f = f;
    this->r = r;
}

// Деструктор класса CTrap.
CTrap::~CTrap()
{
}

// Метод отрисовки.
void CTrap::Draw(HDC dc)
{
    HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
    HBRUSH brush = CreateSolidBrush(RGB(255, 100, 50));
    double rDraw = 10;
    SelectObject(dc, pen);
    SelectObject(dc, brush);
    Ellipse(dc, (x - rDraw), (y - rDraw), (x + rDraw), (y + rDraw));
    pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    brush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    SelectObject(dc, pen);
    SelectObject(dc, brush);
}

// Метод воздействия на шары.
void CTrap::Effect(CBall* ball)
{
    // Вычисление разницы координат по оси абсции и ординат
    // между шаром и центром ловушки.
    double xDist = this->x - ball->GetX();
    double yDist = this->y - ball->GetY();

    // Затем квадрат этих разностей складывает и
    // находим корень из этого.
    double xDistSqr = xDist * xDist;
    double yDistSqr = yDist * yDist;
    double distSqr = xDistSqr + yDistSqr;
    double dist = sqrt(distSqr);
    // Таким образом мы нашли расстояние между центром
    // ловушки и шаров по формуле нахождения длины вектора.

    // Если расстояние между шаром и ловушкой больше чем
    // радиус ловушки, то выход из функции.
    if (dist > this->r)
        return;

    // Если растояние слишком маленькое между ловушкой
    // и шаром, то ограничиваем его. Это может произойти,
    // если движется очень быстро между кадрами
    if (distSqr < 0.6)
        distSqr = 0.6;

    // В данном фрагменте расчитываются коэффициенты, на которые
    // должны измениться координаты шара, после взаимодействия
    // с ловушкой.
    //
    // Мы берем разницу в координат по оси и умножает на наш
    // коэффициент притяжение к ловушке. Деление в формуле
    // на длины необходимо, чтобы коэффициенты были пропорциональны
    // длине между шаром и ловушкой, т.е. воздействие будет
    // более физичное, нежели без этого, т.к. чем ближе
    // будет шар в ловушке, тем сильнее его будет отталкивать
    double xCoef = (this->f * (xDist / dist)) / distSqr;
    double yCoef = (this->f * (yDist / dist)) / distSqr;

    // изменение скорости шара по оси абсции
    double tmpVx = ball->GetVx();
    tmpVx += xCoef;
    ball->SetVx(tmpVx);

    // изменение скорости шара по оси ординат
    double tmpVy = ball->GetVy();
    tmpVy += yCoef;
    ball->SetVy(tmpVy);
}
