#include "my_widgetpen.h"

my_widgetpen::my_widgetpen(QWidget *parent)
    : QWidget{parent}
{
    im_created=false;
}

void my_widgetpen::paintEvent(QPaintEvent *)//переопределяем событие
{
    if (im_created)
    {
        QPainter painter (this);
        painter.drawImage(0,0,im);
    }
}


void my_widgetpen::create_im(int SizeX, int SizeY)
{
    if (!im_created)
    {
        im=QImage(SizeX,SizeY,QImage::Format_ARGB32_Premultiplied);//высота и ширина окна
        im_created=true;
    }
}
