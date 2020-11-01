#ifndef CCOLOREDBALL_H
#define CCOLOREDBALL_H

#include "cball.h"
#include "windows.h"

class CColoredBall : public CBall {

public:
    CColoredBall();
    virtual ~CColoredBall() override;

    virtual void SetColor(unsigned char r, unsigned char g, unsigned char b) override;
    virtual void Draw(HDC& dc) override;

protected:
    HBRUSH brush;
};

#endif // CCOLOREDBALL_H
