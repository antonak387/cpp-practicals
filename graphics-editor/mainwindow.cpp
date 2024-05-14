#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): //конструктор
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    this->setWindowTitle("Графический редактор");//название

    ui->widget->create_im(ui->widget->width(),ui->widget->height());//создаем изображение размером с виджет
    ui->lineEdit_x1->hide();//прячем ненужное
    ui->label_3->hide();
    ui->lineEdit_x2->hide();
    ui->label_5->hide();
    ui->lineEdit_y1->hide();
    ui->label_4->hide();
    ui->lineEdit_y2->hide();
    ui->label_6->hide();


    ui->comboBox_penStyle->findData(2);//выбираем стиль карандаша как 2

    ui->comboBox_penStyle->hide();
    ui->label_penStyle->hide();

    ui->label->hide();
    ui->spinBox_widht->hide();

    ui->comboBox_brushStyle->hide();
    ui->label_brushStyle->hide();



    no_auto_change = true; //авточендж

    size = 0;
}

MainWindow::~MainWindow()//деструктор
{
    delete ui;
}



void MainWindow::on_pushButton_draw_clicked()//нарисовать
{
    int index;

    index=ui->comboBox->currentIndex();//выбираем операцию


    switch (index)
    {

    case 0://точка
    {


        int x=0,y=0;
        QString str;
        bool fl;
        pixel my_pixel;     //создаем переменную пиксель

        str.clear();        //очищаем  строку
        str.append(ui->lineEdit_x->text()); //передаем значения в строку
        x=str.toInt(&fl);                   //образуем флаг
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_y->text());
            y=str.toInt(&fl);
        }
        //color
        if(fl && my_pixel.SetXY(x,y))       // нет ошибок и выбрано х и у
        {
            int a,r,g,b;  //цвет
            QColor color;
            color = QColorDialog::getColor(Qt::black,this,"Выберите цвет пикселя",QColorDialog::ShowAlphaChannel);   //вызываем диалог цветов
            color.getRgb(&r,&g,&b,&a);
            if (color.isValid())//если цвет выбран
            {
                my_pixel.SetRGB(r,g,b,a);
                my_pixel.SetXY(x,y);
                my_pixel.draw(ui->widget->im);
                repaint();//перерисовать

            }

        }

        else
        {
            QMessageBox::warning(this, "Ошибка", "Введены некорректные значения");  //злобно (добро) ругательное сообщение
        }
        break;
    }

    case 1://линия
    {

        int x=0,y=0,x1=0,y1=0;
        QString str;
        bool fl;
        line line;

        str.clear();
        str.append(ui->lineEdit_x->text());
        x=str.toInt(&fl);
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_y->text());
            y=str.toInt(&fl);
        }
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_x1->text());
            x1=str.toInt(&fl);
        }
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_y1->text());
            y1=str.toInt(&fl);
        }

        //color
        if(fl && line.st.SetXY(x,y) && line.end.SetXY(x1,y1)) // если выбраны кнопки
        {
            int a=0,r=0,g=0,b=0;
            QColor color;
            color.getRgb(&r,&g,&b,&a);
            line.mpen.SetWidht(ui->spinBox_widht->value());//выбор толщины
            line.mpen.SetStyle(ui->comboBox_penStyle->currentIndex());//выбор стиля

            if (ui->comboBox_penStyle->currentIndex()!=0) //если выбран стиль границы (кроме "нет линии"), тогда спрашиваем цвет
            {
                color = QColorDialog::getColor(Qt::black,this,"Выберите цвет границы",QColorDialog::ShowAlphaChannel);//выбираем цвет
                color.getRgb(&r,&g,&b,&a);
            }
            if (color.isValid())//если цвет выбран
            {
                line.mpen.SetRGB(r,g,b,a);

                line.st.SetXY(x,y);
                line.end.SetXY(x1,y1);
                line.draw(ui->widget->im);
                repaint();
            }

        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Введены некорректные значения");//злобно  ругательное сообщение
        }
        break;
    }

    case 2://прямоугольник
    {

        int x=0,y=0,x1=0,y1=0;
        QString str;
        bool fl;
        rectangle m_rect; // создаем прямоугольник

        str.clear();//чистим сроку
        str.append(ui->lineEdit_x->text());
        x=str.toInt(&fl);//флаг на
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_y->text());
            y=str.toInt(&fl);
        }
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_x1->text());
            x1=str.toInt(&fl);
        }
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_y1->text());
            y1=str.toInt(&fl);
        }

        //color
        if(fl)
        {
            int a=0,r=0,g=0,b=0;
            QColor color;
            color.getRgb(&r,&g,&b,&a);
            m_rect.mpen.SetWidht(ui->spinBox_widht->value());   // выбираем стиль заливки
            m_rect.mpen.SetStyle(ui->comboBox_penStyle->currentIndex());// выбираем стиль карандаша

            if (ui->comboBox_penStyle->currentIndex()!=0) //если выбран стиль границы (кроме "нет линии"), тогда спрашиваем цвет
            {
                color = QColorDialog::getColor(Qt::black,this,"Выберите цвет границы",QColorDialog::ShowAlphaChannel);
                color.getRgb(&r,&g,&b,&a);
            }
            if ((color.isValid()) || (ui->comboBox_penStyle->currentIndex()==0))//если цвет выбран
            {

                m_rect.mpen.SetRGB(r,g,b,a);
                m_rect.mbrush.SetStyle(ui->comboBox_brushStyle->currentIndex());

                if (ui->comboBox_brushStyle->currentIndex()!=0)//если выбран стиль заливки (кроме "нет заливки"), тогда спрашиваем цвет
                {
                    color = QColorDialog::getColor(Qt::black,this,"Выберите цвет заливки",QColorDialog::ShowAlphaChannel);
                    color.getRgb(&r,&g,&b,&a);
                }
                if (color.isValid())//если цвет выбран
                {
                    m_rect.mbrush.SetRGB(r,g,b,a);

                    m_rect.top_left.SetXY(x,y);
                    m_rect.botton_right.SetXY(x1,y1);
                    m_rect.draw(ui->widget->im);
                    repaint();
                }
            }

        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Введены некорректные значения");//злобно (добро) ругательное сообщение
        }
        break;
    }

    case 3://круг
    {


        int x=0,y=0,rad=0;
        QString str;
        bool fl;
        circle m_circle;

        str.clear();
        str.append(ui->lineEdit_x->text());
        x=str.toInt(&fl);
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_y->text());
            y=str.toInt(&fl);
        }
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_x1->text());
            rad=str.toInt(&fl);
        }


        //color
        if(fl)
        {
            int a=0,r=0,g=0,b=0;
            QColor color;
            color.getRgb(&r,&g,&b,&a);
            m_circle.mpen.SetWidht(ui->spinBox_widht->value());
            m_circle.mpen.SetStyle(ui->comboBox_penStyle->currentIndex());

            if (ui->comboBox_penStyle->currentIndex()!=0) //если выбран стиль границы (кроме "нет линии"), тогда спрашиваем цвет
            {
                color = QColorDialog::getColor(Qt::black,this,"Выберите цвет границы",QColorDialog::ShowAlphaChannel);
                color.getRgb(&r,&g,&b,&a);
            }
            if ((color.isValid()) || (ui->comboBox_penStyle->currentIndex()==0))//если цвет выбран
            {
                m_circle.mpen.SetRGB(r,g,b,a);
                m_circle.mbrush.SetStyle(ui->comboBox_brushStyle->currentIndex());

                if (ui->comboBox_brushStyle->currentIndex()!=0)//если выбран стиль заливки (кроме "нет заливки"), тогда спрашиваем цвет
                {
                    color = QColorDialog::getColor(Qt::black,this,"Выберите цвет заливки",QColorDialog::ShowAlphaChannel);
                    color.getRgb(&r,&g,&b,&a);
                }
                if (color.isValid())//если цвет выбран
                {
                    m_circle.mbrush.SetRGB(r,g,b,a);

                    m_circle.start.SetXY(x,y);
                    m_circle.SetR(rad);

                    m_circle.draw(ui->widget->im);
                    repaint();
                }
            }
        }

        else
        {
            QMessageBox::warning(this, "Ошибка", "Введены некорректные значения");//злобно (добро) ругательное сообщение
        }
        break;
    }

    case 4://эллипс
    {


        int x=0,y=0,rad1=0,rad2=0;
        QString str;
        bool fl;
        ellipse m_el;

        str.clear();
        str.append(ui->lineEdit_x->text());
        x=str.toInt(&fl);
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_y->text());
            y=str.toInt(&fl);
        }
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_x1->text());
            rad1=str.toInt(&fl);
        }
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_y1->text());
            rad2=str.toInt(&fl);
        }


        //color
        if(fl && m_el.start.SetXY(x,y) && m_el.SetR1(rad1) && m_el.SetR2(rad2))
        {
            int a,r,g,b;
            QColor color;
            color.getRgb(&r,&g,&b,&a);
            m_el.mpen.SetWidht(ui->spinBox_widht->value());
            m_el.mpen.SetStyle(ui->comboBox_penStyle->currentIndex());

            if (ui->comboBox_penStyle->currentIndex()!=0) //если выбран стиль границы (кроме "нет линии"), тогда спрашиваем цвет
            {
                color = QColorDialog::getColor(Qt::black,this,"Выберите цвет границы",QColorDialog::ShowAlphaChannel);
                color.getRgb(&r,&g,&b,&a);
            }
            if ((color.isValid()) || (ui->comboBox_penStyle->currentIndex()==0))//если цвет выбран
            {
                m_el.mpen.SetRGB(r,g,b,a);
                m_el.mbrush.SetStyle(ui->comboBox_brushStyle->currentIndex());

                if (ui->comboBox_brushStyle->currentIndex()!=0)//если выбран стиль заливки (кроме "нет заливки"), тогда спрашиваем цвет
                {
                    color = QColorDialog::getColor(Qt::black,this,"Выберите цвет заливки",QColorDialog::ShowAlphaChannel);
                    color.getRgb(&r,&g,&b,&a);
                }
                if (color.isValid())//если цвет выбран
                {
                    m_el.mbrush.SetRGB(r,g,b,a);

                    m_el.start.SetXY(x,y);
                    m_el.SetR(rad1,rad2);

                    m_el.draw(ui->widget->im);
                    repaint();

                }
            }


        }


        else
        {
            QMessageBox::warning(this, "Ошибка", "Введены некорректные значения");//злобно (добро) ругательное сообщение
        }
        break;
    }


    case 5://дуга
    {

        int x=0,y=0,rad1=0,rad2=0,startA=0,spanA=0;
        QString str;
        bool fl;
        arc m_arc;//создаем дугу

        str.clear();
        str.append(ui->lineEdit_x->text());
        x=str.toInt(&fl);
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_y->text());
            y=str.toInt(&fl);
        }
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_x1->text());
            rad1=str.toInt(&fl);
        }
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_y1->text());
            rad2=str.toInt(&fl);
        }
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_x2->text());
            startA=str.toInt(&fl);
        }
        if (fl)
        {
            str.clear();
            str.append(ui->lineEdit_y2->text());
            spanA=str.toInt(&fl);
        }


        //color
        if(fl)
        {
            int a=0,r=0,g=0,b=0;
            QColor color;
            color.getRgb(&r,&g,&b,&a);
            m_arc.mpen.SetWidht(ui->spinBox_widht->value());
            m_arc.mpen.SetStyle(ui->comboBox_penStyle->currentIndex());

            if (ui->comboBox_penStyle->currentIndex()!=0) //если выбран стиль границы (кроме "нет линии"), тогда спрашиваем цвет
            {
                color = QColorDialog::getColor(Qt::black,this,"Выберите цвет границы",QColorDialog::ShowAlphaChannel);
                color.getRgb(&r,&g,&b,&a);
            }
            if (color.isValid())//если цвет выбран
            {
                m_arc.mpen.SetRGB(r,g,b,a);

                m_arc.start.SetXY(x,y);
                m_arc.rad_el.SetR(rad1,rad2);
                m_arc.SetAngles(startA,spanA);
                m_arc.draw(ui->widget->im);
                repaint();
            }


        }

        else
        {
            QMessageBox::warning(this, "Ошибка", "Введены некорректные значения");//злобно (добро) ругательное сообщение
        }
        break;
    }


    case 6://ломаная линия
    {
        polyline m_lom;
        d_table m_table;
        m_table.exec();
        int a=0,r=0,g=0,b=0;
        QColor color;
        color.getRgb(&r,&g,&b,&a);


        if (m_table.GetFlag_v())
        {
            m_table.GetMas(arr,size);

            m_lom.SetArray(size);

            for (int i = 0; i < size; i++)
            {
                m_lom.array[i].SetX(arr[i]);
                m_lom.array[i].SetY(arr[i+size]);
            }


            m_lom.mpen.SetWidht(ui->spinBox_widht->value());
            m_lom.mpen.SetStyle(ui->comboBox_penStyle->currentIndex());

            if (ui->comboBox_penStyle->currentIndex()!=0) //если выбран стиль границы (кроме "нет линии"), тогда спрашиваем цвет
            {
                color = QColorDialog::getColor(Qt::black,this,"Выберите цвет границы",QColorDialog::ShowAlphaChannel);
                color.getRgb(&r,&g,&b,&a);
            }
            if (color.isValid())//если цвет выбран
            {
                m_lom.mpen.SetRGB(r, g, b, a);
                m_lom.mpen.SetWidht(ui->spinBox_widht->value());
                m_lom.mpen.SetStyle(ui->comboBox_penStyle->currentIndex());
                m_lom.draw(ui->widget->im, size);
                repaint();
            }
        }

        break;
    }
    case 7://многоугольник
    {
        polygon m_mnog;
        d_table m_table;
        m_table.exec();
        int a,r,g,b;
        QColor color;
        color.getRgb(&r,&g,&b,&a);


        if (m_table.GetFlag_v())
        {
            m_table.GetMas(arr,size);

            m_mnog.SetArray(size);

            for (int i = 0; i < size; i++)
            {
                m_mnog.array[i].SetX(arr[i]);
                m_mnog.array[i].SetY(arr[i+size]);
            }


            m_mnog.mpen.SetWidht(ui->spinBox_widht->value());
            m_mnog.mpen.SetStyle(ui->comboBox_penStyle->currentIndex());

            if (ui->comboBox_penStyle->currentIndex()!=0) //если выбран стиль границы (кроме "нет линии"), тогда спрашиваем цвет
            {
                color = QColorDialog::getColor(Qt::black,this,"Выберите цвет границы",QColorDialog::ShowAlphaChannel);
                color.getRgb(&r,&g,&b,&a);
            }


            if ((color.isValid()))//если цвет выбран
            {
                m_mnog.mpen.SetRGB(r,g,b,a);
                m_mnog.mbrush.SetStyle(ui->comboBox_brushStyle->currentIndex());
            }
                if (ui->comboBox_brushStyle->currentIndex()!=0)//если выбран стиль заливки (кроме "нет заливки"), тогда спрашиваем цвет
                {
                    color = QColorDialog::getColor(Qt::black,this,"Выберите цвет заливки",QColorDialog::ShowAlphaChannel);
                    color.getRgb(&r,&g,&b,&a);
                }

                if (color.isValid())//если цвет выбран
                {
                    m_mnog.mbrush.SetRGB(r,g,b,a);
                    m_mnog.draw(ui->widget->im, size);
                    repaint();

                }

        }


        break;
    }
    default:
    {
        break;
    }

    }
}

void MainWindow::on_comboBox_activated(int index)
{
    if (index==0)//точка
    {
        ui->lineEdit_x->show();
        ui->label_1->show();
        ui->label_1->setText("x");
        ui->lineEdit_y->show();
        ui->label_2->show();
        ui->label_2->setText("y");
        ui->lineEdit_x1->hide();
        ui->label_3->hide();
        ui->lineEdit_x2->hide();
        ui->label_5->hide();
        ui->lineEdit_y1->hide();
        ui->label_4->hide();
        ui->lineEdit_y2->hide();
        ui->label_6->hide();

        ui->comboBox_penStyle->hide();
        ui->label_penStyle->hide();

        ui->label->hide();
        ui->spinBox_widht->hide();

        ui->comboBox_brushStyle->hide();
        ui->label_brushStyle->hide();


    }
    if (index==1)//линия
    {
        ui->lineEdit_x->show();
        ui->label_1->show();
        ui->label_1->setText("x1");
        ui->lineEdit_y->show();
        ui->label_2->show();
        ui->label_2->setText("y1");
        ui->lineEdit_x1->show();
        ui->label_3->show();
        ui->label_3->setText("x2");
        ui->lineEdit_x2->hide();
        ui->label_5->hide();
        ui->lineEdit_y1->show();
        ui->label_4->show();
        ui->label_4->setText("y2");
        ui->lineEdit_y2->hide();
        ui->label_6->hide();

        ui->comboBox_penStyle->show();
        ui->label_penStyle->show();

        ui->label->show();
        ui->spinBox_widht->show();

        ui->comboBox_brushStyle->hide();
        ui->label_brushStyle->hide();

        if (ui->comboBox_penStyle->currentIndex()==0)
        {
            ui->label->hide();
            ui->spinBox_widht->hide();
        }
        else
        {
            ui->label->show();
            ui->spinBox_widht->show();

        }


    }
    if (index==2)//прямоугольник
    {
        ui->lineEdit_x->show();
        ui->label_1->show();
        ui->label_1->setText("x1");
        ui->lineEdit_y->show();
        ui->label_2->show();
        ui->label_2->setText("y1");
        ui->lineEdit_x1->show();
        ui->label_3->show();
        ui->label_3->setText("x2");
        ui->lineEdit_x2->hide();
        ui->label_5->hide();
        ui->lineEdit_y1->show();
        ui->label_4->show();
        ui->label_4->setText("y2");
        ui->lineEdit_y2->hide();
        ui->label_6->hide();

        ui->comboBox_penStyle->show();
        ui->label_penStyle->show();

        ui->label->show();
        ui->spinBox_widht->show();

        ui->comboBox_brushStyle->show();
        ui->label_brushStyle->show();


        if (ui->comboBox_penStyle->currentIndex()==0)
        {
            ui->label->hide();
            ui->spinBox_widht->hide();
        }
        else
        {
            ui->label->show();
            ui->spinBox_widht->show();

        }


    }
    if (index==3)//круг
    {
        ui->lineEdit_x->show();
        ui->label_1->show();
        ui->label_1->setText("x");
        ui->lineEdit_y->show();
        ui->label_2->show();
        ui->label_2->setText("y");
        ui->lineEdit_x1->show();
        ui->label_3->show();
        ui->label_3->setText("r");
        ui->lineEdit_x2->hide();
        ui->label_5->hide();
        ui->lineEdit_y1->hide();
        ui->label_4->hide();
        ui->lineEdit_y2->hide();
        ui->label_6->hide();

        ui->comboBox_penStyle->show();
        ui->label_penStyle->show();

        ui->label->show();
        ui->spinBox_widht->show();

        ui->comboBox_brushStyle->show();
        ui->label_brushStyle->show();


        if (ui->comboBox_penStyle->currentIndex()==0)
        {
            ui->label->hide();
            ui->spinBox_widht->hide();
        }
        else
        {
            ui->label->show();
            ui->spinBox_widht->show();

        }


    }
    if (index==4)//эллипс
    {
        ui->lineEdit_x->show();
        ui->label_1->show();
        ui->label_1->setText("x");
        ui->lineEdit_y->show();
        ui->label_2->show();
        ui->label_2->setText("y");
        ui->lineEdit_x1->show();
        ui->label_3->show();
        ui->label_3->setText("r1");
        ui->lineEdit_x2->hide();
        ui->label_5->hide();
        ui->lineEdit_y1->show();
        ui->label_4->show();
        ui->label_4->setText("r2");
        ui->lineEdit_y2->hide();
        ui->label_6->hide();

        ui->comboBox_penStyle->show();
        ui->label_penStyle->show();

        ui->label->show();
        ui->spinBox_widht->show();

        ui->comboBox_brushStyle->show();
        ui->label_brushStyle->show();


        if (ui->comboBox_penStyle->currentIndex()==0)
        {
            ui->label->hide();
            ui->spinBox_widht->hide();
        }
        else
        {
            ui->label->show();
            ui->spinBox_widht->show();

        }

    }
    if (index==5)//дуга
    {
        ui->lineEdit_x->show();
        ui->label_1->show();
        ui->label_1->setText("x");
        ui->lineEdit_y->show();
        ui->label_2->show();
        ui->label_2->setText("y");
        ui->lineEdit_x1->show();
        ui->label_3->show();
        ui->label_3->setText("r1");
        ui->lineEdit_x2->hide();
        ui->label_5->hide();
        ui->lineEdit_y1->show();
        ui->label_4->show();
        ui->label_4->setText("r2");
        ui->lineEdit_x2->show();
        ui->label_5->show();
        ui->lineEdit_y2->show();
        ui->label_6->show();

        ui->comboBox_penStyle->show();
        ui->label_penStyle->show();

        ui->label->show();
        ui->spinBox_widht->show();

        ui->comboBox_brushStyle->hide();
        ui->label_brushStyle->hide();


        if (ui->comboBox_penStyle->currentIndex()==0)
        {
            ui->label->hide();
            ui->spinBox_widht->hide();
        }
        else
        {
            ui->label->show();
            ui->spinBox_widht->show();

        }


    }

    if (index==6)//ломаная линия
    {
        ui->lineEdit_x->hide();
        ui->label_1->hide();
        ui->lineEdit_y->hide();
        ui->label_2->hide();
        ui->lineEdit_x1->hide();
        ui->label_3->hide();
        ui->lineEdit_x2->hide();
        ui->label_5->hide();
        ui->lineEdit_y1->hide();
        ui->label_4->hide();
        ui->lineEdit_y2->hide();
        ui->label_6->hide();

        ui->comboBox_penStyle->show();
        ui->label_penStyle->show();

        ui->label->show();
        ui->spinBox_widht->show();

        ui->comboBox_brushStyle->hide();
        ui->label_brushStyle->hide();



        if (ui->comboBox_penStyle->currentIndex()==0)
        {
            ui->label->hide();
            ui->spinBox_widht->hide();
        }
        else
        {
            ui->label->show();
            ui->spinBox_widht->show();

        }
    }

    if (index==7)//многоугольник
    {
        ui->lineEdit_x->hide();
        ui->label_1->hide();
        ui->lineEdit_y->hide();
        ui->label_2->hide();
        ui->lineEdit_x1->hide();
        ui->label_3->hide();
        ui->lineEdit_x2->hide();
        ui->label_5->hide();
        ui->lineEdit_y1->hide();
        ui->label_4->hide();
        ui->lineEdit_y2->hide();
        ui->label_6->hide();

        ui->comboBox_penStyle->show();
        ui->label_penStyle->show();

        ui->label->show();
        ui->spinBox_widht->show();

        ui->comboBox_brushStyle->show();
        ui->label_brushStyle->show();




        if (ui->comboBox_penStyle->currentIndex()==0)
        {
            ui->label->hide();
            ui->spinBox_widht->hide();
        }
        else
        {
            ui->label->show();
            ui->spinBox_widht->show();

        }
    }



}


void MainWindow::on_pushButton_clear_clicked()//очистка
{
    ui->widget->im.fill(0);
    repaint();
}



void MainWindow::on_lineEdit_x_textChanged(const QString &arg1)//если изменили lineedit
{
    if (no_auto_change)
    {

        int f;
        bool flag;
        QPalette p;
        p=ui->lineEdit_x->palette();


        f=ui->lineEdit_x->text().toInt(&flag);


        if (flag && f>=0) // если значение конвертировалось в Int и подходит под условие
        {

            p.setColor(QPalette::Base,Qt::white);
            ui->lineEdit_x->setPalette(p);
        }
        else // если значение не конвертировалось в Int
        {

            p.setColor(QPalette::Base,Qt::red);
            ui->lineEdit_x->setPalette(p);
        }
    }
}


void MainWindow::on_lineEdit_y_textChanged(const QString &arg1)//если изменили lineedit
{
    if (no_auto_change)
    {
        int f;
        bool flag;
        QPalette p;
        p=ui->lineEdit_y->palette();


        f=ui->lineEdit_y->text().toInt(&flag);


        if (flag && f>=0) // если значение конвертировалось в Int и подходит под условие
        {

            p.setColor(QPalette::Base,Qt::white);
            ui->lineEdit_y->setPalette(p);
        }
        else // если значение не конвертировалось в Int
        {

            p.setColor(QPalette::Base,Qt::red);
            ui->lineEdit_y->setPalette(p);
        }
    }
}


void MainWindow::on_lineEdit_x1_textChanged(const QString &arg1)//если изменили lineedit
{
    if (no_auto_change)
    {
        int f;
        bool flag;
        QPalette p;
        p=ui->lineEdit_x1->palette();


        f=ui->lineEdit_x1->text().toInt(&flag);


        if (flag && f>0) // если значение конвертировалось в Int  и подходит под условие
        {

            p.setColor(QPalette::Base,Qt::white);
            ui->lineEdit_x1->setPalette(p);
        }
        else // если значение не конвертировалось в Int
        {

            p.setColor(QPalette::Base,Qt::red);
            ui->lineEdit_x1->setPalette(p);
        }
    }
}


void MainWindow::on_lineEdit_y1_textChanged(const QString &arg1)//если изменили lineedit
{
    if (no_auto_change)
    {
        int f;
        bool flag;
        QPalette p;
        p=ui->lineEdit_y1->palette();


        f=ui->lineEdit_y1->text().toInt(&flag);


        if (flag && f>0) // если значение конвертировалось в Int  и подходит под условие
        {

            p.setColor(QPalette::Base,Qt::white);
            ui->lineEdit_y1->setPalette(p);
        }
        else // если значение не конвертировалось в Int
        {

            p.setColor(QPalette::Base,Qt::red);
            ui->lineEdit_y1->setPalette(p);
        }
    }
}


void MainWindow::on_lineEdit_x2_textChanged(const QString &arg1)//если изменили lineedit
{
    if (no_auto_change)
    {
        int f;
        bool flag;
        QPalette p;
        p=ui->lineEdit_x2->palette();


        f=ui->lineEdit_x2->text().toInt(&flag);


        if (flag && f>=-360 && f<=360) // если значение конвертировалось в Int и подходит под условие
        {

            p.setColor(QPalette::Base,Qt::white);
            ui->lineEdit_x2->setPalette(p);
        }
        else // если значение не конвертировалось в Int
        {

            p.setColor(QPalette::Base,Qt::red);
            ui->lineEdit_x2->setPalette(p);
        }
    }
}


void MainWindow::on_lineEdit_y2_textChanged(const QString &arg1)//если изменили lineedit
{
    if (no_auto_change)
    {
        int f;
        bool flag;
        QPalette p;
        p=ui->lineEdit_y2->palette();


        f=ui->lineEdit_y2->text().toInt(&flag);


        if (flag && f>=-360 && f<=360) // если значение конвертировалось в Int  и подходит под условие
        {

            p.setColor(QPalette::Base,Qt::white);
            ui->lineEdit_y2->setPalette(p);
        }
        else // если значение не конвертировалось в Int
        {

            p.setColor(QPalette::Base,Qt::red);
            ui->lineEdit_y2->setPalette(p);
        }
    }
}



void MainWindow::on_comboBox_penStyle_activated(int index)//изменили стиль линии
{
    if (index==0)
    {
        ui->label->hide();
        ui->spinBox_widht->hide();
    }
    else
    {
        ui->label->show();
        ui->spinBox_widht->show();

    }
}
