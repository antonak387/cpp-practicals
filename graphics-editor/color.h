#ifndef COLOR_H
#define COLOR_H


class color
{
public:
    color();
    void SetRGB(int r, int g, int b, int a=255);
    void GetRGB(int &r, int &g, int &b, int &a);

protected:
    int red;
    int green;
    int blue;
    int alpha; //прозрачность
};

#endif // COLOR_H
