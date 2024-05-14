#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileSave=true;
    isNewFile=true;
    fileName="Безымянный";
    this->setWindowTitle(fileName+" - Блокнот");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_open_triggered()
{
    if(fileSave==false)
    {
        QMessageBox::StandardButton answer = QMessageBox::question(this, "Сохраняем?", "Вы хотите сохранить изменения в файле " + fileName + "?" ,
                                                                   QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(answer!=QMessageBox::Cancel)
        {
            if(isNewFile==true)
            {
                if(answer==QMessageBox::Yes)
                {
                    on_action_saveAs_triggered();
                }
            }
            else
            {
                if(answer==QMessageBox::Yes)
                {
                    on_action_save_triggered();
                }
            }




            //QString fileName;//имя файла
            //fileName = QFileDialog::getOpenFileName(this,"Открыть файл", "C:\\Users\\tohag\\Desktop\\", tr("Text file(*.txt)"));
            //или линукс стиль
            //fileName= QFileDialog::getOpenFileName(this,"Открыть файл", "C:/Users/student/Document", tr("Text file(*txt)"));

            QString fileFlag;//проверка на существование выбранного файла
            fileFlag = QFileDialog::getSaveFileName(this,"Сохранить файл", "C:\\Users\\tohag\\Desktop\\*.txt", tr("Text file(*.txt)"));

            if (fileFlag.isEmpty())//выбран ли файл
            {//не выбран
                QMessageBox::information(this, "Ошибка", "Файл не выбран",QMessageBox::Ok);
            }
            else
            {
                fileName=fileFlag;
                QFile file;
                file.setFileName(fileName);// свыязать файловый поток с файлом
                file.open(QIODevice::ReadOnly);//открыть файл

                int64_t size;//размер файла;

                size = file.size();

                QByteArray ba;
                ba= file.read(size);

                ui->textEdit->clear();
                ui->textEdit->append(QString(ba));

                this->setWindowTitle(fileName+" - Блокнот");
                file.close();
                fileSave=true;
                isNewFile=false;
            }
        }

    }
    else
    {
        QString fileFlag;//проверка на существование выбранного файла
        fileFlag = QFileDialog::getSaveFileName(this,"Сохранить файл", "C:\\Users\\tohag\\Desktop\\*.txt", tr("Text file(*.txt)"));
        if (fileFlag.isEmpty())//выбран ли файл
        {//не выбран
            QMessageBox::information(this, "Ошибка", "Файл не выбран",QMessageBox::Ok);
        }
        else
        {
            fileName=fileFlag;
            QFile file;
            file.setFileName(fileName);// свыязать файловый поток с файлом
            file.open(QIODevice::ReadOnly);//открыть файл

            int64_t size;//размер файла;

            size = file.size();

            QByteArray ba;
            ba= file.read(size);

            ui->textEdit->clear();
            ui->textEdit->append(QString(ba));

            this->setWindowTitle(fileName+" - Блокнот");
            file.close();
            fileSave=true;
            isNewFile=false;
        }
    }
}


void MainWindow::on_action_saveAs_triggered()
{
    QString fileFlag;//проверка на существование выбранного файла
    fileFlag = QFileDialog::getSaveFileName(this,"Сохранить файл", "C:\\Users\\tohag\\Desktop\\*.txt", tr("Text file(*.txt)"));

    if (fileFlag.isEmpty())//выбран ли файл
    {//не выбран
        QMessageBox::information(this, "Ошибка", "Файл не выбран",QMessageBox::Ok);
    }
    else
    {
        fileName = fileFlag;
        QFile file;
        file.setFileName(fileName);// свыязать файловый поток с файлом
        file.open(QIODevice::WriteOnly);//открыть файл
        file.write(ui->textEdit->toPlainText().toUtf8());
        this->setWindowTitle(fileName+" - Блокнот");
        file.close();
        fileSave = true;
        isNewFile=false;
    }
}

void MainWindow::on_action_exit_triggered()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent * event)
{

    if(fileSave==false)
    {
        QMessageBox::StandardButton answer = QMessageBox::question(this, "Сохраняем?", "Вы хотите сохранить изменения в файле? " + fileName + "?",
                                                                   QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(answer!=QMessageBox::Cancel)
        {
            if(isNewFile==true)
            {
                if(answer==QMessageBox::Yes)
                {
                    on_action_saveAs_triggered();
                }
            }
            else
            {
                if(answer==QMessageBox::Yes)
                {
                    on_action_save_triggered();
                }
            }
            if(QMessageBox::question(this,"Выходим?","Точно выходим?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            event->accept();
            else
            event->ignore();
        }
    }
    else
    {
        if(QMessageBox::question(this,"Выходим?","Точно выходим?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        event->accept();
        else
        event->ignore();
    }
}

void MainWindow::on_action_save_triggered()
{

    if(isNewFile==true){
        MainWindow::on_action_saveAs_triggered();
    }
    else{
        QFile file;
        file.setFileName(fileName);// свыязать файловый поток с файлом
        file.open(QIODevice::WriteOnly);//открыть файл
        this->setWindowTitle(fileName+" - Блокнот");
        file.write(ui->textEdit->toPlainText().toUtf8());
        file.close();
        fileSave = true;
        isNewFile=false;
    }
}

void MainWindow::on_action_create_triggered()
{
    if(fileSave==false)
    {
        QMessageBox::StandardButton answer = QMessageBox::question(this, "Сохраняем?", "Вы хотите сохранить изменения в файле? " + fileName + "?",
                                                                   QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(answer!=QMessageBox::Cancel)
        {
            if(isNewFile==true)
            {
                if(answer==QMessageBox::Yes)
                {
                    on_action_saveAs_triggered();
                }
            }
            else
            {
                if(answer==QMessageBox::Yes)
                {
                    on_action_save_triggered();
                }
            }
            fileName="Безымянный";
            isNewFile=true;
            ui->textEdit->clear();
            fileSave=true;
            this->setWindowTitle("Безымянный - Блокнот");
        }
    }
    else
    {
        fileName="Безымянный";
        isNewFile=true;
        ui->textEdit->clear();
        fileSave=true;
        this->setWindowTitle("Безымянный - Блокнот");
    }




  /*  if(fileSave==false)
    {
        if(isNewFile==true)
        {
            if(ui->textEdit->toPlainText().toUtf8()==nullptr)
            {
                QMessageBox::information(this, "Ошибка", "Файл итак чист",QMessageBox::Ok);
            }
            else
            {
                if(QMessageBox::question(this, "Сохраняем?", "Вы хотите сохранить изменения в файле?" , QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
                {
                    on_action_saveAs_triggered();
                }
                fileName="Безымянный";
                isNewFile=true;
                ui->textEdit->clear();
                fileSave=true;
                this->setWindowTitle("Безымянный - Блокнот");
            }
        }
        else
        {
            if(QMessageBox::question(this,"Сохраняем?","Вы хотите сохранить изменения в файле " + fileName + "?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
                on_action_save_triggered();
                fileName="Безымянный";
                isNewFile=true;
                ui->textEdit->clear();
                fileSave=true;
                this->setWindowTitle("Безымянный - Блокнот");

            }
            else {
                fileName="Безымянный";
                isNewFile=true;
                ui->textEdit->clear();
                fileSave=true;
                this->setWindowTitle("Безымянный - Блокнот");
            }
        }
    }
    else {
        fileName="Безымянный";
        isNewFile=true;
        ui->textEdit->clear();
        fileSave=true;
        this->setWindowTitle("Безымянный - Блокнот");
    }*/
}


void MainWindow::on_textEdit_textChanged()
{
    fileSave=false;
    this->setWindowTitle("*"+fileName+" - Блокнот");
}
