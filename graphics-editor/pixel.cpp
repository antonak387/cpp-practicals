#include "pixel.h"

pixel::pixel()//конструктор
{

}

void pixel::draw(QImage &im) //рисуем пиксель
{
    QPainter painter(&im);//создаем рисунок, в нем будем рисовать


    QPen pen;//карандаш
    pen.setWidth(5);//выбираем толщину

    QColor color;  //цвета
    color.setRgb(red,green,blue,alpha);
    pen.setColor(color);
    painter.setPen(pen);

    painter.drawPoint(x, y);//рисуем точку
}
