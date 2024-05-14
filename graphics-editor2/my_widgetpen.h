#ifndef MY_WIDGETPEN_H
#define MY_WIDGETPEN_H

#include <QWidget>
#include <QPainter>

class my_widgetpen : public QWidget
{
    Q_OBJECT
public:
    explicit my_widgetpen(QWidget *parent = nullptr);
    QImage im;
    void create_im(int SizeX, int SizeY);

signals:

protected:

    void paintEvent(QPaintEvent *);
private:
    bool im_created;

};

#endif // MY_WIDGETPEN_H
