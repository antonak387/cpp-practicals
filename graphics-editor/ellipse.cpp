#include "ellipse.h"

ellipse::ellipse()//конструктор
{
  rad1=0;
  rad2=0;
}

bool ellipse::SetR1(int new_r1)//ввод радиуса 1
{

    if (new_r1>0)
    {
        rad1 = new_r1;
        return true;
    }
    else
        return false;
}

bool ellipse::SetR2(int new_r2)//ввод радиуса 2
{
    if (new_r2>0)
    {
        rad2 = new_r2;
        return true;
    }
    else
        return false;
}

bool ellipse::SetR(int new_r1, int new_r2)//ввод радиусов
{

    if ((new_r1 > 0) && (new_r2 >0))
    {
        rad1 = new_r1;
        rad2 = new_r2;
        return true;

    }
    else
    {
        return false;
    }
}
void ellipse::GetR(int &cur_x, int &cur_y) //берем радиусы
{
    cur_x=rad1;
    cur_y=rad2;
}

int ellipse::GetR1()// берем один радиус
{
    return(rad1);
}

int ellipse::GetR2()//берем второй радиус
{
    return(rad2);
}

void ellipse::draw(QImage &im)//рисуем элипс
{
    QPainter painter(&im);
    painter.setRenderHint(QPainter::Antialiasing);//выбираем параметр антиилиастинг
    QPen pen;

    QColor color;
    int r,g,b,a;
    mpen.GetRGB(r,g,b,a);
    color.setRgb(r,g,b,a);
    pen.setColor(color);

    pen.setWidth(mpen.GetWight());//толщина

    pen.setStyle(Qt::PenStyle(mpen.GetStyle()));//стиль линиии

    painter.setPen(pen);

    QBrush brush;//наша заливка
    mbrush.GetRGB(r,g,b,a);
    color.setRgb(r,g,b,a);
    brush.setColor(color);

    brush.setStyle(Qt::BrushStyle(mbrush.GetStyle()));//стиль заливки
    painter.setBrush(brush);

    int x,y,rad1,rad2;
    rad1=GetR1();
    rad2=GetR2();
    x=start.GetX();
    y=start.GetY();


    painter.drawEllipse(x-rad1,y-rad2,rad1*2,rad2*2);
}
