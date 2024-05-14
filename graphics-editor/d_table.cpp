#include "d_table.h"
#include "ui_d_table.h"

d_table::d_table(QWidget *parent) : //конструктор
    QDialog(parent),
    ui(new Ui::d_table)
{
    ui->setupUi(this);
    this->setWindowTitle("Координаты точек");
    flag_vixod = false;
    mas=nullptr;

}

d_table::~d_table()//деструктор
{
    delete ui;
}

void d_table::on_spinBox_valueChanged(int arg1)//изменили значение спинбокса
{
     ui->tableWidget->setRowCount(arg1);
}


void d_table::on_tableWidget_cellChanged(int row, int column)//изменили ячейку
{
    if (no_auto_change)
    {
        bool flag;

        int x = ui->tableWidget->item(row, column)->text().toInt(&flag);

        if (flag && x>=0) // если значение в клетке конвертировалось в Int
            ui->tableWidget->item(row, column)->setBackground(Qt::white);
        else // если значение в клетке не конвертировалось в Int
            ui->tableWidget->item(row, column)->setBackground(Qt::red);
    }
}


void d_table::on_pushButton_random_clicked()//заполнить рандомными значениями
{
    int row = ui->tableWidget->rowCount();
    int val;
    no_auto_change = false;

    for (int i=0; i < row; i++)
    {
        if (ui->tableWidget->item(i,0) == nullptr) //проверка существования ячейки
        {//не существует
            //создаем ячейку
            QTableWidgetItem * ti; //создали указатель
            ti = new QTableWidgetItem; //выделили память
            ui->tableWidget->setItem(i, 0, ti); //поместили ячейку в таблицу
        }
        if (ui->tableWidget->item(i,1) == nullptr) //проверка существования ячейки
        {//не существует
            //создаем ячейку
            QTableWidgetItem * ti; //создали указатель
            ti = new QTableWidgetItem; //выделили память
            ui->tableWidget->setItem(i, 1, ti); //поместили ячейку в таблицу
        }
        val = rand()%1079+1;
        ui->tableWidget->item(i, 0)->setBackground(Qt::white);
        ui->tableWidget->item(i, 0)->setText(QString::number(val));
        val = rand()%499+1;
        ui->tableWidget->item(i, 1)->setBackground(Qt::white);
        ui->tableWidget->item(i, 1)->setText(QString::number(val));
    }
    no_auto_change = true;
}


void d_table::on_pushButton_clicked()//кнопка нарисовать
{
    no_auto_change = false;

    int size = ui->tableWidget->rowCount();
    bool flag; // признак успешного преоб-я ячейки
    bool gl_flag = true; // признак успешного формирования массива
    bool flag_error = false; // признак ошибочности формирования ячейки

    delete [] mas;
    mas=nullptr;

    mas = new int[2*size];

    // форм-е массива
    for (int i = 0; i < size; i++)
    {
        if (ui->tableWidget->item(i, 0) == nullptr) // проверка существования ячейки
        {
            if (!flag_error)
            {
                ui->tableWidget->selectRow(i);
                ui->tableWidget->scrollToItem(ui->tableWidget->item(i, 0));
            }
            flag_error = true;

            gl_flag = false; // если ячейка без значений
            QTableWidgetItem * ti; // создание указателя
            ti = new QTableWidgetItem; // выделение памяти

            ui->tableWidget->setItem(i, 0, ti); // поместили ячейку в таблицу
            ui->tableWidget->item(i, 0)->setBackground(Qt::red);
        }
        else // если существует
        {
            mas[i] = ui->tableWidget->item(i, 0)->text().toInt(&flag);

            int x = ui->tableWidget->item(i, 0)->text().toInt(&flag);

            if (flag && x>=0)
            {
                ui->tableWidget->item(i, 0)->setBackground(Qt::white);
            }
            else
            {
                if (!flag_error)
                {
                    ui->tableWidget->selectRow(i);
                    ui->tableWidget->scrollToItem(ui->tableWidget->item(i, 0));
                }
                flag_error = true;

                gl_flag = false; // если ячейка без значений
                ui->tableWidget->item(i, 0)->setBackground(Qt::red);
            }
        }


        if (ui->tableWidget->item(i, 1) == nullptr) // проверка существования ячейки
        {
            if (!flag_error)
            {
                ui->tableWidget->selectRow(i);
                ui->tableWidget->scrollToItem(ui->tableWidget->item(i, 1));
            }
            flag_error = true;

            gl_flag = false; // если ячейка без значений
            QTableWidgetItem * ti; // создание указателя
            ti = new QTableWidgetItem; // выделение памяти

            ui->tableWidget->setItem(i, 1, ti); // поместили ячейку в таблицу
            ui->tableWidget->item(i, 1)->setBackground(Qt::red);
        }
        else // если существует
        {
            mas[i+size] = ui->tableWidget->item(i, 1)->text().toInt(&flag);

            int x = ui->tableWidget->item(i, 1)->text().toInt(&flag);

            if (flag && x>=0)
            {
                ui->tableWidget->item(i, 1)->setBackground(Qt::white);
            }
            else
            {
                if (!flag_error)
                {
                    ui->tableWidget->selectRow(i);
                    ui->tableWidget->scrollToItem(ui->tableWidget->item(i, 1));
                }
                flag_error = true;

                gl_flag = false; // если ячейка без значений
                ui->tableWidget->item(i, 1)->setBackground(Qt::red);
            }
        }
    }

    if (gl_flag) // если массив сформирован
    {
        flag_vixod=true;
        this->close();
    }
    else // если что-то не так
    {
        flag_vixod=false;
        QMessageBox::information(this,"Ошибка","Таблица содержит некорректные значения", QMessageBox::Ok);
    }
    no_auto_change = true;
}

void d_table::SetMas(int *m, int size)
{
    if (m != nullptr)
    {
        ui->spinBox->setValue(size);

        for (int i = 0; i < size; i++)
        {
            if (ui->tableWidget->item(i, 0) == nullptr)
            {
                QTableWidgetItem * ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i, 0, ti);
            }

            if (ui->tableWidget->item(i, 1) == nullptr)
            {
                QTableWidgetItem * ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i, 1, ti);
            }

            ui->tableWidget->item(i, 0)->setText(QString::number(m[i ]));
            ui->tableWidget->item(i, 1)->setText(QString::number(m[i + size]));
        }
    }
}

void d_table::GetMas(int *&m, int &size) // вызываем массив
{
    size = ui->spinBox->value();

    m = new int [size * 2];

    for (int i = 0; i < size; i++)
    {
        m[i] =  ui->tableWidget->item(i,0)->text().toInt();
        m[i + size] = ui->tableWidget->item(i, 1)->text().toInt();
    }
}
bool d_table::GetFlag_v()//получение флага выхода
{
    return flag_vixod;
}


void d_table::on_pushButton_AddRow_clicked()//добавить строку
{
    ui->spinBox->setValue(ui->spinBox->value()+1);
}


void d_table::on_pushButton_DelRow_clicked()//удалить строку
{
   ui->spinBox->setValue(ui->spinBox->value()-1);
}


void d_table::on_pushButton_2_clicked()
{

    ui->tableWidget->setRowCount(42);
    ui->spinBox->setValue(42);
    no_auto_change = false;
    int row = ui->tableWidget->rowCount();
    int val;
    int meow[84]={(0+10)*(-25)+500,(-4+10)*(-25)+500,(1+10)*(-25)+500,(-8+10)*(-25)+500,(2+10)*(-25)+500,(-8+10)*(-25)+500,(2+10)*(-25)+500,(-2+10)*(-25)+500,(4+10)*(-25)+500,(-8+10)*(-25)+500,(5+10)*(-25)+500,(-8+10)*(-25)+500,(4+10)*(-25)+500,(2+10)*(-25)+500,(3+10)*(-25)+500,(3+10)*(-25)+500,(4+10)*(-25)+500,(5+10)*(-25)+500,(4+10)*(-25)+500,(7+10)*(-25)+500,(3+10)*(-25)+500,(8+10)*(-25)+500,(2+10)*(-25)+500,(10+10)*(-25)+500,(1+10)*(-25)+500,(8+10)*(-25)+500,(-2+10)*(-25)+500,(6+10)*(-25)+500,(-4+10)*(-25)+500,(6+10)*(-25)+500,(-2+10)*(-25)+500,(3+10)*(-25)+500,(-1+10)*(-25)+500,(2+10)*(-25)+500,(-4+10)*(-25)+500,(0+10)*(-25)+500,(-5+10)*(-25)+500,(-2+10)*(-25)+500,(-5+10)*(-25)+500,(-5+10)*(-25)+500,(-7+10)*(-25)+500,(-5+10)*(-25)+500,(-9+10)*(-25)+500,(-6+10)*(-25)+500,(-10+10)*(-25)+500,(-7+10)*(-25)+500,(-10+10)*(-25)+500,(-8+10)*(-25)+500,(-9+10)*(-25)+500,(-9+10)*(-25)+500,(-7+10)*(-25)+500,(-10+10)*(-25)+500,(-3+10)*(-25)+500,(-10+10)*(-25)+500,(-2+10)*(-25)+500,(-9+10)*(-25)+500,(-4+10)*(-25)+500,(-8+10)*(-25)+500,(-6+10)*(-25)+500,(-8+10)*(-25)+500,(-7+10)*(-25)+500,(-7+10)*(-25)+500,(-6+10)*(-25)+500,(-6+10)*(-25)+500,(-5+10)*(-25)+500,(-6+10)*(-25)+500,(-3+10)*(-25)+500,(-8+10)*(-25)+500,(1+10)*(-25)+500,(-8+10)*(-25)+500,(0+10)*(-25)+500,(-7+10)*(-25)+500,(-2+10)*(-25)+500,(-7+10)*(-25)+500,(-1+10)*(-25)+500,(-7+10)*(-25)+500,(0+10)*(-25)+500,(-6+10)*(-25)+500,(0+10)*(-25)+500,(-4+10)*(-25)+500,(-1+10)*(-25)+500,(-3+10)*(-25)+500,(-2+10)*(-25)+500,(-3+10)*(-25)+500};

    for (int i=0; i < row; i++)
    {
        if (ui->tableWidget->item(i,0) == nullptr) //проверка существования ячейки
        {//не существует
            //создаем ячейку
            QTableWidgetItem * ti; //создали указатель
            ti = new QTableWidgetItem; //выделили память
            ui->tableWidget->setItem(i, 0, ti); //поместили ячейку в таблицу
        }
        if (ui->tableWidget->item(i,1) == nullptr) //проверка существования ячейки
        {//не существует
            //создаем ячейку
            QTableWidgetItem * ti; //создали указатель
            ti = new QTableWidgetItem; //выделили память
            ui->tableWidget->setItem(i, 1, ti); //поместили ячейку в таблицу
        }

            val = meow[2*i];
            ui->tableWidget->item(i, 0)->setBackground(Qt::white);
            ui->tableWidget->item(i, 0)->setText(QString::number(val));
            val = meow[2*i+1];
            ui->tableWidget->item(i, 1)->setBackground(Qt::white);
            ui->tableWidget->item(i, 1)->setText(QString::number(val));

    }
    no_auto_change = true;
}

void d_table::on_pushButton_gav_clicked()
{

    ui->tableWidget->setRowCount(30);
    ui->spinBox->setValue(30);
    no_auto_change = false;
    int row = ui->tableWidget->rowCount();
    int val;
    int meow[60]={(-4+10)*-25+500,(-7+10)*-25+500,(-6+10)*-25+500,(-1+10)*-25+500,(-7+10)*-25+500,(4+10)*-25+500,(-8+10)*-25+500,(4+10)*-25+500,(-10+10)*-25+500,(3+10)*-25+500,(-11+10)*-25+500,(5+10)*-25+500,(-8+10)*-25+500,(7+10)*-25+500,(-6+10)*-25+500,(7+10)*-25+500,(-6+10)*-25+500,(6+10)*-25+500,(-6+10)*-25+500,(5+10)*-25+500,(-7+10)*-25+500,(5+10)*-25+500,(-8+10)*-25+500,(6+10)*-25+500,(-8+10)*-25+500,(7+10)*-25+500,(-6+10)*-25+500,(7+10)*-25+500,(-5+10)*-25+500,(6+10)*-25+500,(-4+10)*-25+500,(4+10)*-25+500,(-2+10)*-25+500,(3+10)*-25+500,(4+10)*-25+500,(3+10)*-25+500,(5+10)*-25+500,(2+10)*-25+500,(9+10)*-25+500,(4+10)*-25+500,(5+10)*-25+500,(1+10)*-25+500,(5+10)*-25+500,(-3+10)*-25+500,(6+10)*-25+500,(-7+10)*-25+500,(5+10)*-25+500,(-7+10)*-25+500,(4+10)*-25+500,(-5+10)*-25+500,(1+10)*-25+500,(0+10)*-25+500,(-2+10)*-25+500,(-1+10)*-25+500,(-3+10)*-25+500,(-1+10)*-25+500,(-3+10)*-25+500,(-7+10)*-25+500,(-4+10)*-25+500,(-7+10)*-25+500};

    for (int i=0; i < row; i++)
    {
        if (ui->tableWidget->item(i,0) == nullptr) //проверка существования ячейки
        {//не существует
            //создаем ячейку
            QTableWidgetItem * ti; //создали указатель
            ti = new QTableWidgetItem; //выделили память
            ui->tableWidget->setItem(i, 0, ti); //поместили ячейку в таблицу
        }
        if (ui->tableWidget->item(i,1) == nullptr) //проверка существования ячейки
        {//не существует
            //создаем ячейку
            QTableWidgetItem * ti; //создали указатель
            ti = new QTableWidgetItem; //выделили память
            ui->tableWidget->setItem(i, 1, ti); //поместили ячейку в таблицу
        }

            val = meow[2*i];
            ui->tableWidget->item(i, 0)->setBackground(Qt::white);
            ui->tableWidget->item(i, 0)->setText(QString::number(val));
            val = meow[2*i+1];
            ui->tableWidget->item(i, 1)->setBackground(Qt::white);
            ui->tableWidget->item(i, 1)->setText(QString::number(val));

    }
    no_auto_change = true;
}
