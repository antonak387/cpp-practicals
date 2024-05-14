#ifndef M_BRUSH_H
#define M_BRUSH_H

#include <color.h>

class m_brush : public color
{
public:
    m_brush();


    bool SetStyle(int n_s);
    int GetStyle(void);

    //bool GetStyle (int &t_s);
protected:
    int style;
};

#endif // M_BRUSH_H
