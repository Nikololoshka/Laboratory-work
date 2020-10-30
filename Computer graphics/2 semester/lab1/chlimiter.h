#ifndef CHLIMITER_H
#define CHLIMITER_H

#include <windows.h>

class CHLimiter {

public:
    CHLimiter(int xmin, int xmax, int y);
    ~CHLimiter();
    void Draw(HDC& dc);
    int GetMaxX();
    int GetMinX();
    int GetY();
    void MoveX(int inc);
    void MoveY(int inc);

private:
    int y;
    int xmin, xmax;
};

#endif // CHLIMITER_H
