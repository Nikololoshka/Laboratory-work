#include "cbrightball.h"
#include <iostream>

CBrightBall::CBrightBall(int speed)
{
    this->speed = speed;
    create_time = GetTickCount();
}

void CBrightBall::Draw(HDC& dc)
{
    if (r < 255) {
        r += speed;
        if (r > 255) {
            r = 255;
        }

    } else if (g < 255) {
        g += speed;
        if (g > 255) {
            g = 255;
        }

    } else if (b < 255) {
        b += speed;

        if (b > 255) {
            b = 255;
        }
    }

    DeleteBrush(this->brush);
    this->brush = CreateSolidBrush(RGB(r, g, b));
    CColoredBall::Draw(dc);
}

void CBrightBall::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

