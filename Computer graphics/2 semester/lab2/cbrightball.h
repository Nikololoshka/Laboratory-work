#ifndef CBRIGHTBALL_H
#define CBRIGHTBALL_H

#include "ccoloredball.h"

class CBrightBall : public CColoredBall {

public:
    CBrightBall(int speed = 1);

    void Draw(HDC& dc) override;
    void SetColor(unsigned char r, unsigned char g, unsigned char b) override;

private:
    DWORD create_time;

    unsigned int speed;
    unsigned int r, g, b;

};

#endif // CBRIGHTBALL_H
