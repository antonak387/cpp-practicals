#ifndef M_PEN_H
#define M_PEN_H

#include <color.h>

class m_pen : public color
{
public:
    m_pen();

    bool SetWidht(int n_w);
    int GetWight();
    bool SetStyle(int n_s);
    int GetStyle();

protected:
    int widht;
    int style;
};

#endif // M_PEN_H
