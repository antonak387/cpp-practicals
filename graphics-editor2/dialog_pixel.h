#ifndef DIALOG_PIXEL_H
#define DIALOG_PIXEL_H

#include <QDialog>
#include "my_pen.h"

namespace Ui {
class Dialog_pixel;
}

class Dialog_pixel : public QDialog, public my_pen
{
    Q_OBJECT

public:
    explicit Dialog_pixel(QWidget *parent = nullptr);
    ~Dialog_pixel();

    void setValue(my_pen n_pen);
    my_pen m_pen;

private slots:

    void on_Slider_proz_valueChanged(int value);

    void on_Slider_b_valueChanged(int value);

    void on_Slider_g_valueChanged(int value);

    void on_Slider_r_valueChanged(int value);

    void on_pushButton_ok_clicked();

private:
    Ui::Dialog_pixel *ui;
};

#endif // DIALOG_PIXEL_H
