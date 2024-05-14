#ifndef POLYLINE_H
#define POLYLINE_H

#include"tochka.h"
#include"m_pen.h"
#include <QImage>
#include <QPainter>


class polyline
{
public:
    polyline();

    void draw(QImage &im, int k);
    void SetArray(int new_array);

    tochka *array;

    m_pen mpen;

};

#endif // POLYLINE_H
