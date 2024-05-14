#ifndef MAINWINDOW_H
#define MAINWINDOW_H





#include <QMainWindow>
#include <qtimer.h>
#include<QLabel>

#include<QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void timer_tick(void);//событи

    void down_timer_tick(void);//событие

    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_dawnCounter_clicked();

    void on_pushButton_special_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QTimer*timer;//указатель
    int counter;//счетчик

    QTimer * down_timer;
    int down_counter;
    int special_counter;

    int count,s_count,pause_count,pause_s_count;





};

#endif // MAINWINDOW_H
