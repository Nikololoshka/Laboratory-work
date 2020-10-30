#include "chlimiter.h"

// Конструктор класса CHLimiter.
CHLimiter::CHLimiter(int xmin, int xmax, int y)
{
    this->xmin = xmin;
    this->xmax = xmax;
    this->y = y;
}

// Деструктор класса CHLimiter.
CHLimiter::~CHLimiter()
{
}

// Метод отрисовки.
void CHLimiter::Draw(HDC& dc)
{
    ::MoveToEx(dc, this->xmin, this->y, nullptr);
    ::LineTo(dc, this->xmax, this->y);
}

// Метод для получения xmax.
int CHLimiter::GetMaxX()
{
    return this->xmax;
}

// Метод для получения xmin.
int CHLimiter::GetMinX()
{
    return this->xmin;
}

// Метод для получения y.
int CHLimiter::GetY()
{
    return this->y;
}

// Метод перемещения препятствия по X.
void CHLimiter::MoveX(int inc)
{
    this->xmax -= inc;
    this->xmin -= inc;
}
// Метод перемещения препятствия по Y.
void CHLimiter::MoveY(int inc)
{
    this->y -= inc;
}
