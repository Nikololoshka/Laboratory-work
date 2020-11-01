#ifndef CBALLSARRAY_H
#define CBALLSARRAY_H

// Заголовочный файл определения класса CBall.
#include "cball.h"
#include "cbrightball.h"
#include "ccoloredball.h"

// Заголовочный файл определения класса CTrap.
#include "ctrap.h"
#include "ctrapinverted.h"

class CBallsArray {

public:
    CBallsArray(int max_balls);
    virtual ~CBallsArray();

    CBall* Add();
    void Draw(HDC dc);
    void Move(DWORD delta_ticks);
    void SetBounds(RECT bnds);
    void SetGravityFactor(double gF);

    CColoredBall* AddColoredBall();
    CBrightBall* AddBrightBall();
    CTrap* trap;
    CTrapInverted* trapInverted;

private:
    CBall** balls;
    int count;
    int max_balls;
    double gF;
};

#endif // CBALLSARRAY_H
