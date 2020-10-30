#ifndef CRECT_H
#define CRECT_H

#include <windows.h>
#include <windowsx.h>

class CRect {
public:
    CRect(double x, double y, double w, double h);
    ~CRect();
    void Draw(HDC& dc);
    double minX() const;
    double maxX() const;
    double minY() const;
    double maxY() const;

private:
    HBRUSH hBrush;
    double x, y;
    double w, h;
};

#endif // CRECT_H
