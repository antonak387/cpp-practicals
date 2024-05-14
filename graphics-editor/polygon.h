#ifndef POLYGON_H
#define POLYGON_H

#include"tochka.h"
#include"m_pen.h"
#include"m_brush.h"
#include <QImage>
#include <QPainter>

class polygon
{
public:
    polygon();

    void draw(QImage &im, int k);
    void SetArray(int new_array);

    tochka *array;

    m_pen mpen;
    m_brush mbrush;
};

#endif // POLYGON_H
