#include "cballsettingsmonitor.h"

// Заголовочный файл для использования математических функций.
#include <math.h>

// Конструктор класса CBallSettingsMonitor.
CBallSettingsMonitor::CBallSettingsMonitor(void)
{
    this->angle = 45; // Угол по умолчанию.
    this->speed = 50; // Скорость по умолчанию.
}

// Деструктор класса CBallSettingsMonitor.
CBallSettingsMonitor::~CBallSettingsMonitor(void)
{
}

// Метод отрисовки.
void CBallSettingsMonitor::Draw(HDC dc)
{
    // Значение скорости нормализуется, чтобы при скорости 120
    // максимальная длина вектор на изображении была 30.
    double halfspeed = ((this->speed / 120) * 30) / 2;
    double rad_angle = (this->angle / 180) * 3.1415;
    double x = halfspeed * cos(rad_angle);
    double y = halfspeed * sin(rad_angle);

    Rectangle(dc, 0, 0, 30, 30);
    MoveToEx(dc, (15 - x), (15 - y), NULL);
    LineTo(dc, (15 + x), (15 + y));
    Ellipse(dc, (15 + x - 2), (15 + y - 2), (15 + x + 2), (15 + y + 2));
}
// Метод увеличения скорости.
void CBallSettingsMonitor::SpeedUp()
{
    if (this->speed < 120)
        speed++;
}

// Метод уменьшения скорости.
void CBallSettingsMonitor::SpeedDown()
{
    if (this->speed > 10)
        speed--;
}

// Метод увеличения угла направления.
void CBallSettingsMonitor::AngleUp()
{
    angle++;
    if (this->angle >= 360)
        angle = 0;
}

// Метод уменьшения угла направления.
void CBallSettingsMonitor::AngleDown()
{
    angle--;
    if (this->angle <= 0)
        angle = 360;
}

// Метод расчета скоростей по X и по Y.
void CBallSettingsMonitor::GetVxVy(double& vx, double& vy)
{
    double rad_angle = (this->angle / 180) * 3.1415;
    vx = this->speed * cos(rad_angle);
    vy = this->speed * sin(rad_angle);
}
