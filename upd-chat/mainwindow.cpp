#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)//констурктор
{
    ui->setupUi(this);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));

    ui->label_Error->setStyleSheet("QLabel { color: red; }");

    ui->label_Error->setVisible(false);

    ui->lineEdit_Port->setValidator(new QIntValidator(0, 99999, this));

    ui->lineEdit_Our_Port->setValidator(new QIntValidator(0, 99999, this));

    setWindowTitle("Мой чат");

    //ui->lineEdit_Adress->setInputMask("000.000.000.000;_");

    ui->textEdit_My_Ip->setReadOnly(true);
    ui->textEdit_Input->setReadOnly(true);
    ui->textEdit_Output->setReadOnly(true);


    //QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";          // настраиваю валидатор для ip
    //QRegExp ipRegex ("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
    //QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);

    //ui->lineEdit_Adress->setValidator(ipValidator);

    //    QPixmap pixmap("image_path");
    //    QIcon ButtonIcon(pixmap);
    //    button->setIcon(ButtonIcon);
    //    button->setIconSize(pixmap.rect().size());

    ipValidator = nullptr;
    delete ipValidator;

    updsocket = new QUdpSocket(this);

    address = new QHostAddress;


    timer = new QTimer(this);//создание таймера
    counter = 0;//инициализация счетчика
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()),this,SLOT(timer_tick()));//соединение сигнала таймера с обработчиком

}

MainWindow::~MainWindow()//деструктор
{
    delete ui;

    //    updsocket = nullptr;
    //    address = nullptr;

    delete updsocket;
    delete address;

}

void MainWindow::read_data()//обработка поступивших данных
{
    char * data;
    int size;
    size = int (updsocket->pendingDatagramSize());//уточняем обхем данных в очереди
    if(size>0){

        data = new char[size+1];
        updsocket->readDatagram(data,size);
        data[size]=0;//завершающий 0- признак конца строки (так как передаемстроки). можно терминтировать нулем при передаче(даже правильнее)

        QString stroka;
        stroka = QString::fromLocal8Bit(data,size);

        while(stroka.contains("SM.0")){
            int nLol = stroka.lastIndexOf("SM.0");
            QString str = stroka.left(nLol);
            QString oka = stroka.right(stroka.size()-nLol-4);
            stroka = str+"💩"+oka;
        }
        while(stroka.contains("SM.1")){
            int nLol = stroka.lastIndexOf("SM.1");
            QString str = stroka.left(nLol);
            QString oka = stroka.right(stroka.size()-nLol-4);
            stroka = str+"😺"+oka;
        }
        while(stroka.contains("SM.2")){
            int nLol = stroka.lastIndexOf("SM.2");
            QString str = stroka.left(nLol);
            QString oka = stroka.right(stroka.size()-nLol-4);
            stroka = str+"😹"+oka;
        }
        while(stroka.contains("SM.3")){
            int nLol = stroka.lastIndexOf("SM.3");
            QString str = stroka.left(nLol);
            QString oka = stroka.right(stroka.size()-nLol-4);
            stroka = str+"😻"+oka;
        }
        while(stroka.contains("SM.4")){
            int nLol = stroka.lastIndexOf("SM.4");
            QString str = stroka.left(nLol);
            QString oka = stroka.right(stroka.size()-nLol-4);
            stroka = str+"😿"+oka;
        }
        while(stroka.contains("SM.5")){
            int nLol = stroka.lastIndexOf("SM.5");
            QString str = stroka.left(nLol);
            QString oka = stroka.right(stroka.size()-nLol-4);
            stroka = str+"😼"+oka;
        }
        while(stroka.contains("SM.6")){
            int nLol = stroka.lastIndexOf("SM.6");
            QString str = stroka.left(nLol);
            QString oka = stroka.right(stroka.size()-nLol-4);
            stroka = str+"🐈"+oka;
        }



        ui->textEdit_Input->append(stroka);

        delete [] data;

    }
}

void MainWindow::on_pushButton_Create_clicked()//создание соединения
{
    if(isCreate)
    {

        //ui->lineEdit_Port->text().toInt();
        //ui->lineEdit_Our_Port->text().toInt();

        QString str = ui->lineEdit_Adress->text();
        int tSize = str.size();
        int numdot=0;

        our_port = ui->lineEdit_Our_Port->text().toInt();

        port = ui->lineEdit_Port->text().toInt();

        for(int i = 1; i < tSize-1;i++)
        {
            if((str[i-1]<='9'&&str[i-1]>='0')&&str[i]=='.'&&(str[i+1]<='9'&&str[i+1]>='0'))
            {
                numdot++;
            }
        }

        address = new QHostAddress;

        address->setAddress(ui->lineEdit_Adress->text());//получаем адрес другого узла
        numdot=3;
        if(our_port==0||port==0||numdot!=3){
            ui->label_Error->setVisible(true);
            if(numdot!=3){
                ui->label_Error->setText("Введите ip адрес правильно");
                ui->lineEdit_Adress->setStyleSheet("background:#f00;");
                ui->lineEdit_Our_Port->setStyleSheet("background:#fff;");
                ui->lineEdit_Port->setStyleSheet("background:#fff;");
            }
            else {
                if(port==0){
                    ui->label_Error->setText("Введите порт");
                    ui->lineEdit_Adress->setStyleSheet("background:#fff;");
                    ui->lineEdit_Our_Port->setStyleSheet("background:#fff;");
                    ui->lineEdit_Port->setStyleSheet("background:#f00;");
                }
                else {
                    ui->label_Error->setText("Введите наш порт");
                    ui->lineEdit_Adress->setStyleSheet("background:#fff;");
                    ui->lineEdit_Port->setStyleSheet("background:#fff;");
                    ui->lineEdit_Our_Port->setStyleSheet("background:#f00;");
                }
            }

        }

        else {
            ui->lineEdit_Adress->setStyleSheet("background:#fff;");
            ui->lineEdit_Our_Port->setStyleSheet("background:#fff;");
            ui->lineEdit_Port->setStyleSheet("background:#fff;");
            ui->lineEdit_Adress->setEnabled(false);
            ui->lineEdit_Port->setEnabled(false);
            ui->lineEdit_Our_Port->setEnabled(false);
            ui->label_Error->setVisible(false);

            if (updsocket == nullptr) updsocket = new QUdpSocket;
            updsocket->bind(QHostAddress::Any,quint16(our_port));//включаем привязку сокета к порту our port принимаем сообщения с любых адресов
            connect(updsocket,&QUdpSocket::readyRead, this, &MainWindow::read_data);//соединяем сигнал готовности данных с наших слотов обработки

            isCreate = false;
            ui->pushButton_Create->setText("Удалить соединение");
        }
    }
    else
    {
        disconnect(updsocket,&QUdpSocket::readyRead, this, &MainWindow::read_data);
        delete updsocket;
        updsocket = nullptr;
        delete address;
        address = nullptr;

        ui->lineEdit_Adress->setStyleSheet("background:#fff;");
        ui->lineEdit_Our_Port->setStyleSheet("background:#fff;");
        ui->lineEdit_Port->setStyleSheet("background:#fff;");
        ui->lineEdit_Adress->setEnabled(true);
        ui->lineEdit_Our_Port->setEnabled(true);
        ui->lineEdit_Port->setEnabled(true);
        ui->label_Error->setVisible(false);
        isCreate =true;
        ui->pushButton_Create->setText("Создать соединение");



    }

}



void MainWindow::on_pushButton_Send_Mes_clicked()// отправляем сообщение
{
    if(!isCreate){
        if(ui->lineEdit_Send_Mes->text()>""){

            //            QFontDatabase fontDB;
            //            fontDB.addApplicationFont(":/A Font Supporting Emoji.ttf");


            ui->label_Error->setVisible(false);
            ui->lineEdit_Send_Mes->setStyleSheet("background:#fff;");

            char * data;
            int size;

            QString stroka = ui->lineEdit_Send_Mes->text();


            while(stroka.contains("💩")){
                int nLol = stroka.lastIndexOf("💩");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.0"+oka;
            }

            while(stroka.contains("😺")){
                int nLol = stroka.lastIndexOf("😺");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.1"+oka;
            }

            while(stroka.contains("😹")){
                int nLol = stroka.lastIndexOf("😹");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.2"+oka;
            }

            while(stroka.contains("😻")){
                int nLol = stroka.lastIndexOf("😻");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.3"+oka;
            }

            while(stroka.contains("😿")){
                int nLol = stroka.lastIndexOf("😿");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.4"+oka;
            }

            while(stroka.contains("😼")){
                int nLol = stroka.lastIndexOf("😼");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.5"+oka;
            }

            while(stroka.contains("🐈")){
                int nLol = stroka.lastIndexOf("🐈");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.6"+oka;
            }

            size = stroka.length();
            QByteArray ba = stroka.QString::toLocal8Bit();//ui->lineEdit_Send_Mes->text().QString::toLocal8Bit();
            data = ba.data();
            updsocket->writeDatagram(data,size,*address,quint16(port));

            ui->textEdit_Output->append(ui->lineEdit_Send_Mes->text());

            ui->lineEdit_Send_Mes->clear();
        }
        else {
            ui->label_Error->setVisible(true);
            ui->label_Error->setText("Напишите сообщение");
            ui->lineEdit_Send_Mes->setStyleSheet("background:#f00;");
        }
    }

    else {
        QMessageBox::critical(this,"Ошибка","Сперва создайте соединение");
    }
}


//сделать кнопку показать ip
//пересоздание сооединения
// русский язык

//звук при получении сообщений

// передача смайликов
//передача файлов

void MainWindow::on_pushButton_Look_At_Ip_clicked()//посмотрим на ip
{
//    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
//    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
//        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
//        {
//            //ui->textEdit_My_Ip->setText(address.toString());
//            ui->textEdit_My_Ip->append(address.toString());
//        }

//    }

    //ui->textEdit_My_Ip->clear();
    QList<QNetworkInterface> allInterfaces = QNetworkInterface::allInterfaces();
    QNetworkInterface eth;

    foreach(eth, allInterfaces) {
        QList<QNetworkAddressEntry> allEntries = eth.addressEntries();
        QNetworkAddressEntry entry;
        foreach (entry, allEntries) {
            if(entry.ip().toString()!="::1"&&entry.ip().toString()!="127.0.0.1")
            ui->textEdit_My_Ip->append(entry.ip().toString());
        }
    }
}

void MainWindow::on_pushButton_Look_Out_Ip_clicked()// спрячем ip
{
    ui->textEdit_My_Ip->clear();
}


void MainWindow::on_pushButton_Poop_clicked()// нажать на смайлик
{
    ui->lineEdit_Send_Mes->insert("💩");
}

void MainWindow::on_pushButton_Smile_clicked()//нажать на смайлик
{
    ui->lineEdit_Send_Mes->insert("😺");
}
void MainWindow::on_pushButton_Laught_clicked()//нажать на смайлик
{
    ui->lineEdit_Send_Mes->insert("😹");
}
void MainWindow::on_pushButton_Love_clicked()//нажать на смайлик
{
    ui->lineEdit_Send_Mes->insert("😻");
}
void MainWindow::on_pushButton_Cry_clicked()//нажать на смайлик
{
    ui->lineEdit_Send_Mes->insert("😿");
}
void MainWindow::on_pushButton_WrySmile_clicked()//нажать на смайлик
{
    ui->lineEdit_Send_Mes->insert("😼");
}
void MainWindow::on_pushButton_JustCat_clicked()//нажать на смайлик
{
    ui->lineEdit_Send_Mes->insert("🐈");
}

void MainWindow::on_pushButton_Spam_clicked()//спам
{
    if(!isCreate){
        if(ui->lineEdit_Spam->text()>"")
        {
            if(!isSpamNow)
            {

                //ui->lineEdit_Send_Mes->setEnabled(false);
                //ui->pushButton_Send_Mes->setEnabled(false);
                ui->pushButton_Spam->setText("Стоп спам");
                ui->pushButton_Create->setEnabled(false);
                timer->start();
                isSpamNow = true;
            }
            else
            {
                timer->stop();
                isSpamNow = false;
                //ui->lineEdit_Send_Mes->setEnabled(true);
                //ui->pushButton_Send_Mes->setEnabled(true);
                ui->pushButton_Create->setEnabled(true);
                ui->pushButton_Spam->setText("Спам");
            }
        }
        else
        {
            ui->label_Error->setVisible(true);
            ui->label_Error->setText("Напишите сообщение");
            ui->lineEdit_Spam->setStyleSheet("background:#f00;");
        }
    }

    else {
        QMessageBox::critical(this,"Ошибка","Сперва создайте соединение");
    }
}

void MainWindow::timer_tick()//тик таймер отправляем спам
{
    if(!isCreate){
        if(ui->lineEdit_Spam->text()>""){

            //            QFontDatabase fontDB;
            //            fontDB.addApplicationFont(":/A Font Supporting Emoji.ttf");


            ui->label_Error->setVisible(false);
            ui->lineEdit_Spam->setStyleSheet("background:#fff;");

            char * data;
            int size;

            QString stroka = ui->lineEdit_Spam->text();


            while(stroka.contains("💩")){
                int nLol = stroka.lastIndexOf("💩");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.0"+oka;
            }

            while(stroka.contains("😺")){
                int nLol = stroka.lastIndexOf("😺");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.1"+oka;
            }

            while(stroka.contains("😹")){
                int nLol = stroka.lastIndexOf("😹");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.2"+oka;
            }

            while(stroka.contains("😻")){
                int nLol = stroka.lastIndexOf("😻");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.3"+oka;
            }

            while(stroka.contains("😿")){
                int nLol = stroka.lastIndexOf("😿");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.4"+oka;
            }

            while(stroka.contains("😼")){
                int nLol = stroka.lastIndexOf("😼");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.5"+oka;
            }

            while(stroka.contains("🐈")){
                int nLol = stroka.lastIndexOf("🐈");
                QString str = stroka.left(nLol);
                QString oka = stroka.right(stroka.size()-nLol-2);
                stroka = str+"SM.6"+oka;
            }

            size = stroka.length();
            QByteArray ba = stroka.QString::toLocal8Bit();//ui->lineEdit_Send_Mes->text().QString::toLocal8Bit();
            data = ba.data();
            updsocket->writeDatagram(data,size,*address,quint16(port));

            ui->textEdit_Output->append(ui->lineEdit_Spam->text());
        }
        else {
            ui->label_Error->setVisible(true);
            ui->label_Error->setText("Напишите сообщение");
            ui->lineEdit_Spam->setStyleSheet("background:#f00;");
        }
    }

    else {
        QMessageBox::critical(this,"Ошибка","Сперва создайте соединение");
    }
}
