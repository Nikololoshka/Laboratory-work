#include "ctrapinverted.h"

// Заголовочный файл определения математических функций.
#include <math.h>

// Конструктор класса CTrap.
CTrapInverted::CTrapInverted(double x, double y, double f, double r)
{
    this->x = x;
    this->y = y;
    this->f = -f;
    this->r = r;
}

// Деструктор класса CTrap.
CTrapInverted::~CTrapInverted()
{
}

// Метод отрисовки.
void CTrapInverted::Draw(HDC dc)
{
    HPEN pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
    HBRUSH brush = CreateSolidBrush(RGB(50, 100, 255));
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
void CTrapInverted::Effect(CBall* ball)
{
    double xDist = this->x - ball->GetX();
    double yDist = this->y - ball->GetY();
    double xDistSqr = xDist * xDist;
    double yDistSqr = yDist * yDist;
    double distSqr = xDistSqr + yDistSqr;
    double dist = sqrt(distSqr);

    if (dist > this->r)
        return;

    if (distSqr < 0.6)
        distSqr = 0.6;

    double xCoef = (this->f * (xDist / dist)) / distSqr;
    double yCoef = (this->f * (yDist / dist)) / distSqr;

    double tmpVx = ball->GetVx();
    tmpVx += xCoef;
    ball->SetVx(tmpVx);

    double tmpVy = ball->GetVy();
    tmpVy += yCoef;
    ball->SetVy(tmpVy);
}
