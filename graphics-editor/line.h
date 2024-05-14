#ifndef LINE_H
#define LINE_H

#include"tochka.h"
#include"m_pen.h"
#include <QImage>
#include <QPainter>



class line
{
public:
    line();
    void draw(QImage &im);


    tochka st;//старт
    tochka end;//конец


    m_pen mpen;
};

#endif // LINE_H
