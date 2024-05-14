#include "m_brush.h"

m_brush::m_brush()//конструктор
{

    style = 1;

}



bool m_brush::SetStyle(int n_s)//установка стиля
{

    if ((n_s>=0)&&(n_s<=15))
    {
        style=n_s;
        return true;
    }
    else
        return false;


}

int m_brush ::GetStyle()//возвращение стиля
{
    return style;
}
