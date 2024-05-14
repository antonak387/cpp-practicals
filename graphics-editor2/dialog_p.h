#ifndef DIALOG_P_H
#define DIALOG_P_H

#include <QDialog>
#include "my_pen.h"

namespace Ui {
class Dialog_p;
}

class Dialog_p : public QDialog, public my_pen
{
    Q_OBJECT

public:
    explicit Dialog_p(QWidget *parent = nullptr);
    ~Dialog_p();

    void setValue(my_pen n_pen);
    my_pen m_pen;

private slots:
    void on_buttonBox_accepted();

    void on_Slider_proz_valueChanged(int value);

    void on_Slider_b_valueChanged(int value);

    void on_Slider_g_valueChanged(int value);

    void on_Slider_r_valueChanged(int value);

    void on_comboBox_penStyle_currentIndexChanged(int index);

private:
    Ui::Dialog_p *ui;
};

#endif // DIALOG_P_H
