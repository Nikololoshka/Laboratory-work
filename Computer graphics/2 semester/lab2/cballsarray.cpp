#include "cballsarray.h"

// Конструктор класса CBallsArray.
CBallsArray::CBallsArray(int max_balls)
{
    this->count = 0;
    this->max_balls = max_balls;
    this->balls = new CBall*[max_balls];
}

// Деструктор класса CBallsArray.
CBallsArray::~CBallsArray(void)
{
    for (int i = 0; i < count; i++)
        delete this->balls[i];

    delete[] this->balls;
}

// Метод добавления объектов класса CBall в массив.
CBall* CBallsArray::Add()
{
    if (count >= max_balls)
        return NULL;

    count++;
    balls[count - 1] = new CBall();
    return balls[count - 1];
}

// Метод отрисовки.
void CBallsArray::Draw(HDC dc)
{
    for (int i = 0; i < count; i++)
        balls[i]->Draw(dc);
}

// Метод движения.
void CBallsArray::Move(DWORD delta_ticks)
{
// Указатели на объекты класса CBall для расчета столкновений
// между 2-мя шарами
CBall* ball1;
CBall* ball2;

// Перебираем все уникальные пары шаров с помощью
// вложенных циклов.
for (int i = 0; i < count; i++) {
    for (int j = (i + 1); j < count; j++) {
        // Записываем указатели на текущую пару шаров
        ball1 = this->balls[i];
        ball2 = this->balls[j];

        // Теперь найден расстояние между центрами шаров.
        // Для воспользуемся формулой для вычисления длины
        // вектора (но без корня в конце)
        double cx = ball2->GetX() - ball1->GetX();
        double cy = ball2->GetY() - ball1->GetY();
        double cSqr = cx * cx + cy * cy;

        // Eсли растояние между центрами шаров меньше, чем
        // сумма их радиусов, то вычисляем отражение
        //
        // P.s. Здесь "сумма их радиусов" возводится в
        // квадрат, т.к. длина вычислялась без корня в конце
        if (cSqr <= ((ball1->GetR() + ball2->GetR()) * (ball1->GetR() + ball2->GetR()))) {
            // Сначало вычислим скалярное произведение векторов
            double ball1CScalar = ball1->GetVx() * cx + ball1->GetVy() * cy;
            double ball2CScalar = ball2->GetVx() * cx + ball2->GetVy() * cy;

            // Разложим скорости шара № 1 на нормальную и тагенсальную.
            double ball1Nvx = (cx * ball1CScalar) / cSqr;
            double ball1Nvy = (cy * ball1CScalar) / cSqr;
            double ball1Tvx = ball1->GetVx() - ball1Nvx;
            double ball1Tvy = ball1->GetVy() - ball1Nvy;

            // Разложим скорости шара № 2 на нормальную и тагенсальную.
            double ball2Nvx = (cx * ball2CScalar) / cSqr;
            double ball2Nvy = (cy * ball2CScalar) / cSqr;
            double ball2Tvx = ball2->GetVx() - ball2Nvx;
            double ball2Tvy = ball2->GetVy() - ball2Nvy;

            // Нормальная скорость - направленную вдоль линии центров
            // Тагенсальная - перпендикулярная к нормальной

            // Реализация обмена нормальными скоростями
            // (тагенсальные остаются неизменными).
            ball1->SetVx(ball2Nvx + ball1Tvx);
            ball1->SetVy(ball2Nvy + ball1Tvy);
            ball2->SetVx(ball1Nvx + ball2Tvx);
            ball2->SetVy(ball1Nvy + ball2Tvy);
        }
    }
}

// Обработка отражения от стенок
for (int i = 0; i < count; i++)
    balls[i]->Move(delta_ticks);
}

// Метод установления границ.
void CBallsArray::SetBounds(RECT bnds)
{
    for (int i = 0; i < count; i++)
        balls[i]->SetBounds(bnds);
}

// Метод добавления объектов класса CColoredBall в массив.
CColoredBall* CBallsArray::AddColoredBall()
{
    if (count >= max_balls)
        return NULL;

    count++;
    balls[count - 1] = new CColoredBall();
    return (CColoredBall*)(balls[count - 1]);
}

CBrightBall* CBallsArray::AddBrightBall()
{
    if (count >= max_balls)
        return NULL;

    count++;
    balls[count - 1] = new CBrightBall(rand() % 5 + 1);
    return (CBrightBall*)(balls[count - 1]);
}
