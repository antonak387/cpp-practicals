#ifndef CIRCLE_H
#define CIRCLE_H

#include"tochka.h"
#include"m_pen.h"
#include"m_brush.h"
#include <QImage>
#include <QPainter>

#include <QMessageBox>

class circle
{
public:
    circle();
    void draw(QImage &im);

    bool SetR(int new_r);
    int GetR(void);

    tochka start;

    m_pen mpen;
    m_brush mbrush;

protected:
    int rad;
};

#endif // CIRCLE_H
