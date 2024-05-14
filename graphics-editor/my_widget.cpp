#include "my_widget.h"

my_widget::my_widget(QWidget *parent): QWidget{parent}
{

    im_created=false;

}

void my_widget::paintEvent(QPaintEvent *)//переопределяем событие
{
    if (im_created)
    {
        QPainter painter (this);
        painter.drawImage(0,0,im);
    }
}

void my_widget::create_im(int SizeX, int SizeY)//создаем рисунок
{
    if (!im_created)
    {
        im=QImage(SizeX,SizeY,QImage::Format_ARGB32_Premultiplied);//высота и ширина окна
        im_created=true;
    }
}


