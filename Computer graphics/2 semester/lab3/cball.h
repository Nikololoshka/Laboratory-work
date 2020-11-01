#ifndef CBALL_H
#define CBALL_H

#include <vector>
#include <windows.h>
#include <windowsx.h>

class CBall {

public:
    CBall();
    virtual ~CBall();

    virtual void SetParams(double x, double y, double r, double vx, double vy, RECT rect);
    virtual void Draw(HDC& dc);
    void Move(DWORD& delta_ticks);
    void SetBounds(RECT& bnds);

    virtual void SetColor(unsigned char r, unsigned char g, unsigned char b);

    double GetX();
    double GetY();
    double GetVx();
    double GetVy();
    double GetR();
    void SetVx(double vx);
    void SetVy(double vy);

private:
    double x, y;
    double vx, vy;
    double r;
    RECT bounds;
};

#endif // CBALL_H
