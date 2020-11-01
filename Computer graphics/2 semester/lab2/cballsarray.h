#ifndef CBALLSARRAY_H
#define CBALLSARRAY_H

// Заголовочный файл определения класса CBall.
#include "cball.h"
#include "cbrightball.h"
#include "ccoloredball.h"

class CBallsArray {

public:
    CBallsArray(int max_balls);
    virtual ~CBallsArray();

    CBall* Add();
    void Draw(HDC dc);
    void Move(DWORD delta_ticks);
    void SetBounds(RECT bnds);

    CColoredBall* AddColoredBall();
    CBrightBall* AddBrightBall();

private:
    CBall** balls;
    int count;
    int max_balls;
};

#endif // CBALLSARRAY_H
