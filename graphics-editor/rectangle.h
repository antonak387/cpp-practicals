#ifndef RECTANGLE_H
#define RECTANGLE_H

#include"tochka.h"
#include"m_pen.h"
#include"m_brush.h"
#include <QImage>
#include <QPainter>

class rectangle
{
public:
    rectangle();
    void draw(QImage &im);


    tochka top_left;//старт
    tochka botton_right;//конец

  //  color gran;
  // color vnutr;
    m_pen mpen;
    m_brush mbrush;

};

#endif // RECTANGLE_H
