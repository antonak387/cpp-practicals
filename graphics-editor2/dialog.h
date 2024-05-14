#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "my_pen.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog, public my_pen
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void setStyleVisible(bool fl);
    void setValue(my_pen n_pen);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    bool StyleVisible;

};

#endif // DIALOG_H
