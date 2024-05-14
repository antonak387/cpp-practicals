#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#define NUM_THRD 10

#include <QMainWindow>
#include <vector>
#include "my_thread.h"
#include <QDebug>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    my_thread * thrd[NUM_THRD];//указатели на потоки

    int numT;

    int numEnd = 0;

    int nmth;

    int predValSB;


public slots:
    void potok_info(int);// слот для приема сигнала

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_kill_clicked();

    //void timer_tick(void);//событие

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
