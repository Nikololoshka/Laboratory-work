#include "cball.h"

// Конструктор класса CBall.
CBall::CBall()
{
}

// Деструктор класса CBall.
CBall::~CBall()
{
}

// Метод отрисовки.
void CBall::Draw(HDC& dc)
{
    Ellipse(dc, (x - r), (y - r), (x + r), (y + r));
}

// Метод движения.
void CBall::Move(DWORD& delta_ticks)
{
    // Расчет времени между перемещениями в секундах.
    double s_delta = ((double)delta_ticks) / 1000.0;

    // если мы двигаемся направо и пересекаем правую границу экрана, то
    // меняем наше направление по оси абцисс на противоположное
    // (т.е. теперь будем двигаться налево)
    if ((this->x >= (bounds.right - r)) && (this->vx > 0)) {
        this->vx = -(this->vx);
    }

    // если мы двигаемся налево и пересекаем левую границу экрана, то
    // меняем наше направление по оси абцисс на противоположное
    // (т.е. теперь будем двигаться направо)
    if ((this->x <= r) && (this->vx < 0)) {
        this->vx = -(this->vx);
    }

    // если мы двигаемся вниз и пересекаем нижнию границу экрана, то
    // меняем наше направление по оси ординат на противоположное
    // (т.е. теперь будем двигаться наверх)
    if ((this->y >= (bounds.bottom - r)) && (this->vy > 0)) {
        this->vy = -(this->vy);
    }

    // если мы двигаемся наверх и пересекаем верхнию границу экрана, то
    // меняем наше направление по оси ординат на противоположное
    // (т.е. теперь будем двигаться вниз)
    if ((this->y <= r) && (this->vy < 0)) {
        this->vy = -(this->vy);
    }

    // рассчитываем величину перемещение по оси абсции
    double dx = vx * s_delta;
    // рассчитываем величину перемещение по оси ординат
    double dy = vy * s_delta;
    // перемещаем шар по оси абсцисс
    this->x += dx;
    // перемещаем шар по оси ординат
    this->y += dy;
}

// Метод установления границ.
void CBall::SetBounds(RECT& bnds)
{
    this->bounds = bnds;
}

// Установление параметров класса CBall.
void CBall::SetParams(double x, double y, double r, double vx, double vy, RECT rect)
{
    this->x = x;
    this->y = y;
    this->r = r;
    this->vx = vx;
    this->vy = vy;
    this->bounds = rect;
}

// Метод получения координаты X.
double CBall::GetX()
{
    return this->x;
}

// Метод получения координаты Y.
double CBall::GetY()
{
    return this->y;
}

// Метод получения скорости по X VX.
double CBall::GetVx()
{
    return this->vx;
}

// Метод получения скорости по Y VY.
double CBall::GetVy()
{
    return this->vy;
}

// Метод получения радиуса R.
double CBall::GetR()
{
    return this->r;
}

// Метод установления скорости по X VX.
void CBall::SetVx(double vx)
{
    this->vx = vx;
}

// Метод установления скорости по Y VY.
void CBall::SetVy(double vy)
{
    this->vy = vy;
}

// Метод установления цвета (пустой).
void CBall::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
}
