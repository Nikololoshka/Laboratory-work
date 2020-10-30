#include "cball.h"

// Конструктор класса CBall.
CBall::CBall(double x, double y, double vx, double vy, double r)
{
    hBrush = CreateSolidBrush(RGB(0, 255, 0));
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->r = r;
    this->prev_ticks = GetTickCount();
}

// Деструктор класса CBall.
CBall::~CBall()
{
    DeleteObject(hBrush);
}

// Метод отрисовки.
void CBall::Draw(HDC& dc)
{
    HBRUSH hOldBrush;
    hOldBrush = SelectBrush(dc, hBrush);
    Ellipse(dc, (x - r), (y - r), (x + r), (y + r));
    SelectBrush(dc, hOldBrush);
}

// Метод движения.
void CBall::Move(DWORD& ticks)
{
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

    // Обработка реакции на препятствие CHLimiter.
    //
    // если правая сторона нашего объекта (шара) находится правее левой координаты отрезка
    // и левая строна шара находится левее правой координаты отрезка, то...
    if (((this->x + r) >= limit1->GetMinX()) && ((this->x - r) <= limit1->GetMaxX())) {
        // проверяем, двигаемся ли мы вниз. Если да, то...
        if (this->vy > 0) {
            // смотрим, пересекается ли нижняя часть шара по оси ординат с верхней частью отрезка
            if (((limit1->GetY() - this->y) < this->r) && ((limit1->GetY() - this->y) > 0)) {
                // меняем направление шара на противоположное
                // (т.е. теперь будем двигаться наверх)
                this->vy = -(this->vy);
            }
        } else {
            // если нет, то...

            // смотрим, пересекается ли верхняя часть шара по оси ординат с нижней частью отрезка
            if (((this->y - limit1->GetY()) < this->r) && ((this->y - limit1->GetY()) > 0)) {
                // меняем направление шара на противоположное
                // (т.е. теперь будем двигаться вниз)
                this->vy = -(this->vy);
            }
        }
    }

    // Обработка реакции на препятствия CRect.
    for (const auto& rect : this->rects) {
        this->HandlingRect(rect);
    }

    // расчет времени между перемещениями в секундах.
    double s_delta = (static_cast<double>(ticks - this->prev_ticks)) / 1000.0;
    // сохраняем текущие время
    this->prev_ticks = ticks;
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

// Метод передачи препятствия.
void CBall::SetLimiter(CHLimiter* l)
{
    this->limit1 = l;
}

// Метод устанавливает массив с препятствиями (в виде прямоугольников)
void CBall::SetRects(std::vector<CRect*>& rects)
{
    this->rects = rects;
}

// Метод обрабатывает препятсвие CRect
void CBall::HandlingRect(const CRect* rect)
{

    // в зоне прямоугольника по оси абсцисс
    if ((this->x + r >= rect->minX()) && ((this->x - r) <= rect->maxX())) {
        // двигаемся вниз
        if (this->vy > 0) {
            if (((rect->minY() - this->y) < this->r) && ((rect->minY() - this->y) > 0)) {
                this->vy = -(this->vy);
            }
        } else {
            if (((this->y - rect->maxY()) < this->r) && ((this->y - rect->maxY()) > 0)) {
                this->vy = -(this->vy);
            }
        }
    }
    // в зоне прямоугольника по оси ординат
    if ((this->y + r >= rect->minY()) && ((this->y - r) <= rect->maxY())) {
        // двигаемся направо
        if (this->vx > 0) {
            if (((rect->minX() - this->x) < this->r) && ((rect->minX() - this->x) > 0)) {
                this->vx = -(this->vx);
            }
        } else {
            if (((this->x - rect->maxX()) < this->r) && ((this->x - rect->maxX()) > 0)) {
                this->vx = -(this->vx);
            }
        }
    }
}
