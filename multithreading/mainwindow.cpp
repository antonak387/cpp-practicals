#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) ://конструктор
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    setWindowTitle("Потоки");

    ui->textEdit->setReadOnly(true);

    predValSB=1;

    ui->spinBox->setMaximum(NUM_THRD);

    for(int i = 0 ;i <NUM_THRD;i++)
    {
        thrd [i] = new my_thread(rand());//создали потоки
        thrd [i]->com = 0;
        thrd [i]->start();
        connect(thrd[i], SIGNAL(status_upd(int)), this , SLOT(potok_info(int)));//соединили сигналы и слот
    }
}

MainWindow::~MainWindow()//деструктор
{
    delete ui;
    for(int i = 0;i<NUM_THRD;i++)
    {
        qDebug()<<"allright"<<i;
        if(thrd[i]!=nullptr)
        {
            qDebug()<<0;
            thrd[i]->com=4;
            qDebug()<<1;
            thrd[i]->mtx->unlock();
            qDebug()<<2;
            //thrd[i]->terminate();
        }
            qDebug()<<"allright"<<i;
    }
    qDebug()<<"allrightall";
}

void MainWindow::on_pushButton_start_clicked()//нажмем на кнопку старт
{
    numT = ui->spinBox->value();

    for(int i = 0 ; i <numT;i++){
        thrd[i]->com=1;
        thrd[i]->trans=i;
        thrd[i]->mtx->unlock();//разлочили мьютекс
    }

    ui->textEdit->clear();
    ui->pushButton_start->setEnabled(false);
    ui->pushButton_kill->setEnabled(false);
    ui->spinBox->setEnabled(false);

}

void MainWindow::on_pushButton_kill_clicked()//нажмем на кноку убийств
{

    numT = ui->spinBox->value();

    for(int i = 0 ; i <numT;i++){
        thrd[i]->com=2;
        thrd[i]->trans=i;
        thrd[i]->mtx->unlock();
    }

    ui->textEdit->clear();
    ui->pushButton_start->setEnabled(false);
    ui->pushButton_kill->setEnabled(false);
    ui->spinBox->setEnabled(false);
}

void MainWindow::potok_info(int nmth)//при получении сигнала от потока вызывается эта функция
{
    //    if(thrd[nmth]->com==1){
    //        ui->textEdit->append("поток "+ QString::number(nmth+1) +" в работе "+QString::number(thrd[nmth]->stch)+" мсек");
    //    }

    //    if(thrd[nmth]->com==2){
    //        ui->textEdit->append("поток "+ QString::number(nmth+1) +" (умрет) в работе "+QString::number(thrd[nmth]->stch)+" мсек");
    //    }

    if(thrd[nmth]->com==3){
        ui->textEdit->append("поток "+ QString::number(nmth+1) +" отработал "+QString::number(thrd[nmth]->stch)+" мсек");
        numEnd++;
    }
    if(thrd[nmth]->com == 4){
        ui->textEdit->append("поток "+ QString::number(nmth+1) +"  умер, работал "+QString::number(thrd[nmth]->stch)+" мсек");
        delete thrd[nmth];
        thrd[nmth] = nullptr;
    }
    if(numEnd==ui->spinBox->value()){
        ui->pushButton_start->setEnabled(true);
        ui->pushButton_kill->setEnabled(true);
        ui->spinBox->setEnabled(true);
        numEnd=0;
    }

}

void MainWindow::on_spinBox_valueChanged(int arg1)//при изменении значения спинбокса нужно создать или удалить ненужные потоки
{
    if(predValSB>arg1){
        for(int i = predValSB ; i< arg1;i++)
        {
                disconnect(thrd[i], SIGNAL(status_upd(int)), this , SLOT(potok_info(int)));
                thrd [i]->com = 5;
                thrd[i]->trans=i;
                thrd[i]->mtx->unlock();
                //thrd[i]->terminate();
                delete thrd[i];
                thrd[i] = nullptr;
        }
    }

    else {
        for(int i = predValSB ; i <arg1;i++)
        {
            thrd [i] = new my_thread(rand());//создали потоки
            thrd [i]->com = 0;
            thrd [i]->start();
            connect(thrd[i], SIGNAL(status_upd(int)), this , SLOT(potok_info(int)));//соединили сигналы и слот
        }
    }
    predValSB=arg1;
}
