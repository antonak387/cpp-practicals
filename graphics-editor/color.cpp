#include "color.h"

color::color()//конструктор
{
    red=0;
    green=0;
    blue=0;
    alpha=255;
}

void color::SetRGB(int r, int g, int b, int a)//установка цвета
{
    red=r;
    green =g;
    blue = b;
    alpha=a;
}

void color::GetRGB(int &r, int &g, int &b, int &a)//возвращение цвета
{
    r=red;
    g=green;
    b=blue;
    a=alpha;
}
