#ifndef CBALLSETTINGSMONITOR_H
#define CBALLSETTINGSMONITOR_H

// Заголовочный файл, в котором находится описание основных функций Windows API.
#include <windows.h>

class CBallSettingsMonitor {

public:
    CBallSettingsMonitor();
    ~CBallSettingsMonitor();

    void Draw(HDC dc);
    void SpeedUp();
    void SpeedDown();
    void AngleUp();
    void AngleDown();
    void GetVxVy(double& vx, double& vy);

private:
    double angle;
    double speed;
};

#endif // CBALLSETTINGSMONITOR_H
