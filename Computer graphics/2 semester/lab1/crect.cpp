#include "crect.h"

CRect::CRect(double x, double y, double w, double h)
{
    hBrush = CreateSolidBrush(RGB(0, 0, 255));
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

CRect::~CRect()
{
    DeleteObject(hBrush);
}

void CRect::Draw(HDC& dc)
{
    HBRUSH hOldBrush;
    hOldBrush = SelectBrush(dc, hBrush);
    Rectangle(dc, x, y, x + w, y + h);
    SelectBrush(dc, hOldBrush);
}

double CRect::minX() const
{
    return x;
}

double CRect::maxX() const
{
    return x + w;
}

double CRect::minY() const
{
    return y;
}

double CRect::maxY() const
{
    return y + h;
}
