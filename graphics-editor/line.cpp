#include "line.h"

line::line()//конструктор
{

}

void line::draw(QImage &im)//рисуем линию
{
    QPainter painter(&im);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;

    QColor color;
    int r,g,b,a;
    mpen.GetRGB(r,g,b,a);
    color.setRgb(r,g,b,a);
    pen.setColor(color);


    pen.setWidth(mpen.GetWight());//толщина
    pen.setStyle(Qt::PenStyle(mpen.GetStyle()));//стиль линии

    painter.setPen(pen);

    painter.drawLine(st.GetX(),st.GetY(),end.GetX(),end.GetY());
}
