#include "m_pen.h"

m_pen::m_pen() //конструктор
{
    widht = 1;
    style = 0;

}

bool m_pen::SetWidht(int n_w)//установка ширины
{
    if ((n_w>=1)&&(n_w<=21))
    {
        widht=n_w;
        return true;
    }
    else
        return false;
}

int m_pen ::GetWight()//получение ширины
{
    return widht;
}

bool m_pen::SetStyle(int n_s)//установка стиля
{
    if ((n_s>=0)&&(n_s<=5))
    {
        style=n_s;
        return true;
    }
    else
        return false;

}

int m_pen ::GetStyle()//получение стиля
{
    return style;
}
