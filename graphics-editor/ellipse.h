#ifndef ELLIPSE_H
#define ELLIPSE_H

#include"tochka.h"
#include"m_pen.h"
#include"m_brush.h"
#include <QImage>
#include <QPainter>

class ellipse
{
public:
    ellipse();
    void draw(QImage &im);

    bool SetR1(int new_r1);
    int GetR1(void);

    bool SetR2(int new_r2);
    int GetR2(void);

    bool SetR(int new_r1,int new_r2);
    void GetR(int &cur_x, int &cur_y);

    tochka start;

    m_pen mpen;
    m_brush mbrush;

protected:
    int rad1;
    int rad2;
};

#endif // ELLIPSE_H
