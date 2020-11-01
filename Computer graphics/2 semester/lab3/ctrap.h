#ifndef CTRAP_H
#define CTRAP_H

// Заголовочный файл определения класса CBall.
#include "cball.h"
class CTrap {

public:
    CTrap(double x, double y, double f, double r);
    virtual ~CTrap(void);
    void Draw(HDC dc);
    void Effect(CBall* ball);

private:
    // Позиция ловушки.
    double x, y;

    // Коэффициент притяжения к ловушке.
    double f;

    // Расстояние от центра, после которого воздействие ловушки не
    // наблюдается (в остальных случаях сила воздействия обратно пропорциональна
    // квадрату расстояния).
    double r;
};

#endif // CTRAP_H
