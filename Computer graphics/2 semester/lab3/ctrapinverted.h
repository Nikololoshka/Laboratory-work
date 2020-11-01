#ifndef CTRAPINVERTED_H
#define CTRAPINVERTED_H

// Заголовочный файл определения класса CBall.
#include "cball.h"

class CTrapInverted {
public:
    CTrapInverted(double x, double y, double f, double r);
    virtual ~CTrapInverted(void);
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

#endif // CTRAPINVERTED_H
