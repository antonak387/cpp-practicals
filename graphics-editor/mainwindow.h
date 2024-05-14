#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QColorDialog>
#include <pixel.h>
#include <line.h>
#include <rectangle.h>
#include <circle.h>
#include <ellipse.h>
#include <arc.h>
#include <polyline.h>
#include "d_table.h"
#include "polygon.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_draw_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_clear_clicked();

    void on_lineEdit_x_textChanged(const QString &arg1);

    void on_lineEdit_y_textChanged(const QString &arg1);

    void on_lineEdit_x1_textChanged(const QString &arg1);

    void on_lineEdit_y1_textChanged(const QString &arg1);

    void on_lineEdit_x2_textChanged(const QString &arg1);

    void on_lineEdit_y2_textChanged(const QString &arg1);

    void on_comboBox_penStyle_activated(int index);

private:
    Ui::MainWindow *ui;
    bool no_auto_change; // признак не авто ввода
    int row;
    int *arr;
    int size;
};
#endif // MAINWINDOW_H
