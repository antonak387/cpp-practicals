#include "dialog_p.h"
#include "ui_dialog_p.h"

Dialog_p::Dialog_p(QWidget *parent) ://конструктор
    QDialog(parent),
    ui(new Ui::Dialog_p)
{
    ui->setupUi(this);
    this->setWindowTitle("Параметры линии (границы)");

    ui->label_3->setText(QString::number(ui->Slider_proz->value()));
    ui->label_r_2->setText(QString::number(ui->Slider_r->value()));
    ui->label_g_2->setText(QString::number(ui->Slider_g->value()));
    ui->label_b_2->setText(QString::number(ui->Slider_b->value()));


    ui->widget->create_im(ui->widget->width(),ui->widget->height());
    ui->widget->im.fill(0);

}

Dialog_p::~Dialog_p()//деструктор
{
    delete ui;
}

void Dialog_p::setValue(my_pen n_pen)//устанавливаем значения
{

    n_pen.GetColor(alpha,red,green,blue);

    ui->Slider_r->setValue(red);
    ui->Slider_g->setValue(green);
    ui->Slider_b->setValue(blue);
    ui->Slider_proz->setValue(alpha);

    ui->label_r_2->setText(QString::number(red));
    ui->label_g_2->setText(QString::number(green));
    ui->label_b_2->setText(QString::number(blue));
    ui->label_3->setText(QString::number(alpha));

    ui->comboBox_penStyle->setCurrentIndex(n_pen.GetStyle());
    ui->spinBox->setValue(n_pen.GetWidth());


    QPainter painter(&ui->widget->im);
    QColor color;
    QBrush brush;
    color.setRgb(red,green,blue,alpha);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    ui->widget->im.fill(0);
    painter.drawRect(-1,-1,200,200);
    repaint();


}

void Dialog_p::on_buttonBox_accepted()//если ок
{

    red=ui->label_r_2->text().toInt();
    green=ui->label_g_2->text().toInt();
    blue=ui->label_b_2->text().toInt();
    alpha=ui->label_3->text().toInt();

    m_pen.SetStyle(ui->comboBox_penStyle->currentIndex());
    m_pen.SetWidth(ui->spinBox->value());

}


void Dialog_p::on_Slider_proz_valueChanged(int value)//если измении ползунок прозрачность
{
    ui->label_3->setText(QString::number(value));


    //для предпросмотра цвета

    int alpha=value;
    int red =  ui->Slider_r->value();
    int green =  ui->Slider_g->value();
    int blue = ui->Slider_b->value();

    QPainter painter(&ui->widget->im);
    QColor color;
    QBrush brush;
    color.setRgb(red,green,blue,alpha);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    ui->widget->im.fill(0);
    painter.drawRect(-1,-1,200,200);
    repaint();

}


void Dialog_p::on_Slider_b_valueChanged(int value)//если изменили ползунок синего цвета
{
    ui->label_b_2->setText(QString::number(value));


    //для предпросмотра цвета
    int alpha=ui->Slider_proz->value();
    int red =  ui->Slider_r->value();
    int green =  ui->Slider_g->value();
    int blue = value;

    QPainter painter(&ui->widget->im);
    QColor color;
    QBrush brush;
    color.setRgb(red,green,blue,alpha);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    ui->widget->im.fill(0);
    painter.drawRect(-1,-1,200,200);
    repaint();

}


void Dialog_p::on_Slider_g_valueChanged(int value)//если изменили ползунок зеленого цвета
{
    ui->label_g_2->setText(QString::number(value));

    //для предпросмотра цвета
    int alpha=ui->Slider_proz->value();
    int red =  ui->Slider_r->value();
    int green = value;
    int blue =  ui->Slider_b->value();

    QPainter painter(&ui->widget->im);
    QColor color;
    QBrush brush;
    color.setRgb(red,green,blue,alpha);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    ui->widget->im.fill(0);
    painter.drawRect(-1,-1,200,200);
    repaint();

}


void Dialog_p::on_Slider_r_valueChanged(int value)//если изменили ползунок красного цвета
{
    ui->label_r_2->setText(QString::number(value));

    //для предпросмотра цвета
    int alpha=ui->Slider_proz->value();
    int red = value;
    int green = ui->Slider_g->value();
    int blue =  ui->Slider_b->value();
    QPainter painter(&ui->widget->im);
    QColor color;
    QBrush brush;
    color.setRgb(red,green,blue,alpha);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    ui->widget->im.fill(0);
    painter.drawRect(-1,-1,200,200);
    repaint();


}


void Dialog_p::on_comboBox_penStyle_currentIndexChanged(int index)//изменили комбобокс стиля линии
{
    if (index==0)//если нет линии
    {
        ui->label->hide();
        ui->spinBox->hide();
        ui->label_a->hide();
        ui->label_b->hide();
        ui->label_r->hide();
        ui->label_g->hide();
        ui->Slider_b->hide();
        ui->Slider_g->hide();
        ui->Slider_proz->hide();
        ui->Slider_r->hide();

        ui->label_b_2->hide();
        ui->label_r_2->hide();
        ui->label_g_2->hide();
        ui->label_3->hide();
        ui->label_r->hide();
        ui->label_g->hide();
        ui->widget->hide();
    }
    else//если выбран стиль (кроме нет линии)
    {
        ui->label->show();
        ui->spinBox->show();
        ui->label_a->show();
        ui->label_b->show();
        ui->label_r->show();
        ui->label_g->show();
        ui->Slider_b->show();
        ui->Slider_g->show();
        ui->Slider_proz->show();
        ui->Slider_r->show();

        ui->label_b_2->show();
        ui->label_r_2->show();
        ui->label_g_2->show();
        ui->label_3->show();
        ui->label_r->show();
        ui->label_g->show();
        ui->widget->show();
    }
}

