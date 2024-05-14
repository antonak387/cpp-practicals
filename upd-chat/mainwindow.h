#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>//библиотека
#include <QNetworkInterface>
#include <QtMultimedia/QSound>
#include <QMessageBox>
#include <QTextCodec>
#include <QValidator>
#include <QDebug>

#include<QLabel>
#include<QPushButton>
#include<QString>

#include <qtimer.h>


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

    void timer_tick(void);//событие

    void read_data(void);// слот для обработки поступивших данных

    void on_pushButton_Create_clicked();

    void on_pushButton_Send_Mes_clicked();

    void on_pushButton_Look_At_Ip_clicked();

    void on_pushButton_Look_Out_Ip_clicked();

    void on_pushButton_JustCat_clicked();

    void on_pushButton_Cry_clicked();

    void on_pushButton_Laught_clicked();

    void on_pushButton_Poop_clicked();

    void on_pushButton_WrySmile_clicked();

    void on_pushButton_Love_clicked();

    void on_pushButton_Smile_clicked();

    void on_pushButton_Spam_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket * updsocket;// сам udp сокет(указатель на него)
    QHostAddress * address;//для адреса
    int port, our_port;//порты для связи

    bool isCreate = true;
    bool isSpamNow = false;

    QRegExpValidator *ipValidator;

    QTimer*timer;//указатель
    int counter;//счетчик
    QTimer * down_timer;

};

#endif // MAINWINDOW_H
