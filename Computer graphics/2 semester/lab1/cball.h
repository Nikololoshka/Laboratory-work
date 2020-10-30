#ifndef CBALL_H
#define CBALL_H

#include <vector>
#include <windows.h>
#include <windowsx.h>

#include "chlimiter.h"
#include "crect.h"

class CBall {

public:
    CBall(double x, double y, double vx, double vy, double r);
    ~CBall();
    void Draw(HDC& dc);
    void Move(DWORD& ticks);
    void SetBounds(RECT& bnds);
    void SetLimiter(CHLimiter* l);
    void SetRects(std::vector<CRect*>& rects);

private:
    void HandlingRect(const CRect* rect);

private:
    HBRUSH hBrush;
    DWORD prev_ticks;
    double x, y;
    double vx, vy;
    double r;
    RECT bounds;
    CHLimiter* limit1;
    std::vector<CRect*> rects;
};

#endif // CBALL_H
