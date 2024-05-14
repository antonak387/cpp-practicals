#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) ://конструктор
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_pause->setEnabled(false);

    timer = new QTimer(this);//создание таймера
    counter = 0;//инициализация счетчика
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()),this,SLOT(timer_tick()));//соединение сигнала таймера с обработчиком

    down_timer = new QTimer(this);//создание таймера
    down_counter = 0;//инициализация счетчика
    down_timer->setInterval(1000);
    connect(down_timer, SIGNAL(timeout()),this,SLOT(down_timer_tick()));//соединение сигнала таймера с обработчиком

    ui->label->hide();

    ui->spinBox->setValue(10);

    ui->spinBox_timeForStop->setValue(2);

    ui->spinBox_timeForStart->setValue(1);

    ui->lcdNumber->display("00:00:00:00");

    ui->lcdNumber_dawnCounter->display("00:00:10");

    ui->lcdNumber_special->display("00:00:00");


    count = -1;
    s_count = -1;
    pause_count = 0;
    pause_s_count = 0;

    timer->start();

}

MainWindow::~MainWindow()//деструктор
{
    delete ui;
}


void MainWindow::timer_tick()//таймер сразу для двух таймеров
{

    QString str;
    if(count >=0){

        int h=0,m=0,sec=0,s_sec=0;//часы минуты секунды сотые секунды

        s_sec= (counter-count)%100;
        sec=(counter-count)/100;

        m = sec/60;
        sec=sec%60;

        h =m/60;
        m = m%60;


        str.clear();

        if ( h <10)
            str.append("0");
        str.append(QString::number(h)+":");
        if ( m <10)
            str.append("0");
        str.append(QString::number(m)+":");
        if ( sec <10)
            str.append("0");
        str.append(QString::number(sec)+":");
        if ( s_sec <10)
            str.append("0");
        str.append(QString::number(s_sec));

        ui->lcdNumber->display(str);//выводим на счетчик

    }



    if (s_count>=0){
        special_counter = (counter-s_count);
        if (special_counter==ui->spinBox_timeForStart->value()*100)
        {
            count = counter;
            //timer->start();//10 милисекунд 0.01 sek
            ui->pushButton_stop->setEnabled(true);
            ui->pushButton_pause->setEnabled(true);


        }

        if (special_counter==(ui->spinBox_timeForStop->value()+ui->spinBox_timeForStart->value())*100)
        {
            ui->pushButton_stop->setEnabled(false);
            ui->pushButton_pause->setEnabled(false);
            count=-1;
            s_count=-1;
            ui->spinBox_timeForStop->setEnabled(true);
            ui->spinBox_timeForStart->setEnabled(true);


        }


        str.clear();
        int h=0,m=0,sec=0;//часы минуты секунды сотые секунды
        special_counter=special_counter/100;
        sec= special_counter%60;
        m = special_counter/60;
        h =m/60;
        m = m%60;

        if ( h <10)
            str.append("0");
        str.append(QString::number(h));
        str.append(":");
        if ( m <10)
            str.append("0");
        str.append(QString::number(m));
        str.append(":");
        if ( sec <10)
            str.append("0");
        str.append(QString::number(sec));

        ui->lcdNumber_special->display(str);


    }


    counter++;
    pause_count++;
    pause_s_count++;


}

void MainWindow::down_timer_tick()//то что будет по армагедонному таймеру вызываться
{
    if(down_counter>0){
        down_counter--;
    }
    QString str;
    int h,m,sec;//часы минуты секунды сотые секунды
    str.clear();

    sec= down_counter%60;
    m=down_counter/60;
    h =m/60;
    m = m%60;

    if ( h <10)
        str.append("0");
    str.append(QString::number(h)+":");

    if ( m <10)
        str.append("0");
    str.append(QString::number(m)+":");

    if ( sec <10)
        str.append("0");
    str.append(QString::number(sec));


    ui->lcdNumber_dawnCounter->display(str);

    if (down_counter<=0){
        timer->stop();
        ui->label->setVisible(true);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        down_timer->stop();

        ui->pushButton_stop->click();
        ui->pushButton_stop->setEnabled(false);
        ui->pushButton_start->setEnabled(false);
        ui->pushButton_pause->setEnabled(false);
        ui->spinBox->setEnabled(false);
        ui->spinBox_timeForStop->setEnabled(false);
        ui->spinBox_timeForStart->setEnabled(false);

        ui->pushButton_special->setEnabled(false);

    }



}


//void MainWindow::special_timer_tick()//то что будет по таймеру вызываться
//{

//    special_counter++;

//    if (special_counter==ui->spinBox_timeForStart->value())
//    {
//        counter=0;
//        timer->start();//10 милисекунд 0.01 sek
//        ui->pushButton_stop->setEnabled(true);
//        ui->pushButton_pause->setEnabled(true);

//    }

//    if (special_counter==ui->spinBox_timeForStop->value())
//    {
//        timer->stop();
//        ui->pushButton_stop->setEnabled(false);
//        ui->pushButton_pause->setEnabled(false);

//    }


//    QString str; str.clear();
//    int h,m,sec;//часы минуты секунды сотые секунды

//    sec= special_counter%60;
//    m = special_counter/60;
//    h =m/60;
//    m = m%60;

//    if ( h <10)
//        str.append("0");
//    str.append(QString::number(h));
//    str.append(":");
//    if ( m <10)
//        str.append("0");
//    str.append(QString::number(m));
//    str.append(":");
//    if ( sec <10)
//        str.append("0");
//    str.append(QString::number(sec));

//    ui->lcdNumber_special->display(str);

//}


void MainWindow::on_pushButton_start_clicked()// старт 1 таймер
{

    count = counter;
    //timer->start();//10 милисекунд 0.01 sek
    ui->pushButton_stop->setEnabled(true);
    ui->pushButton_pause->setEnabled(true);

}

void MainWindow::on_pushButton_stop_clicked()// стоп 1 таймер
{
    //timer->stop();
    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_pause->setEnabled(false);
    count=-1;

}

void MainWindow::on_pushButton_pause_clicked()//пауза 1 таймер
{
    if(count!=-1){
        //timer->stop();
        pause_count = count ;
        count = -1;
    }
    else {
        //timer->start();
        count = pause_count;
    }

}

void MainWindow::on_pushButton_dawnCounter_clicked()//армагедон
{
    ui->pushButton_dawnCounter->setEnabled(false);
    int time = ui->spinBox->value();
    ui->spinBox->setEnabled(false);
    down_counter=time;
    down_timer->start();

}

void MainWindow::on_pushButton_special_clicked()//спец кнопка
{
    s_count=counter;
    ui->lcdNumber_special->display("00:00:00");
    ui->spinBox_timeForStop->setEnabled(false);
    ui->spinBox_timeForStart->setEnabled(false);


}

void MainWindow::on_spinBox_valueChanged(int arg1)//изменяем значение армагедона
{
    if ( arg1 <10)
        ui->lcdNumber_dawnCounter->display("00:00:0"+QString::number(arg1));
    else
        ui->lcdNumber_dawnCounter->display("00:00:"+QString::number(arg1));
}
