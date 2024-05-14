#ifndef D_TABLE_H
#define D_TABLE_H

#include <QDialog>
#include <QMessageBox>
#include "tochka.h"

namespace Ui
{
class d_table;
}

class d_table : public QDialog
{
    Q_OBJECT

public:
    explicit d_table(QWidget *parent = nullptr);
    ~d_table();
    void SetMas(int *m,int size);
    void GetMas(int *&m, int &size);
    bool GetFlag_v(void);

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_tableWidget_cellChanged(int row, int column);

    void on_pushButton_random_clicked();

    void on_pushButton_clicked();

    void on_pushButton_AddRow_clicked();

    void on_pushButton_DelRow_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_gav_clicked();

private:
    Ui::d_table *ui;
    bool flag_vixod;
    bool no_auto_change; // признак не авто ввода
    int * mas;
};

#endif // D_TABLE_H
