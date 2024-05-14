#include "dialog_pixel.h"
#include "ui_dialog_pixel.h"

Dialog_pixel::Dialog_pixel(QWidget *parent) ://конструктор
    QDialog(parent),
    ui(new Ui::Dialog_pixel)
{
    ui->setupUi(this);
    this->setWindowTitle("Цвет точки");



    ui->label_3->setText(QString::number(ui->Slider_proz->value()));
    ui->label_r_2->setText(QString::number(ui->Slider_r->value()));
    ui->label_g_2->setText(QString::number(ui->Slider_g->value()));
    ui->label_b_2->setText(QString::number(ui->Slider_b->value()));

    ui->Slider_r->setStyleSheet("QSlider::handle:horizontal {background-color: rgb(255, 0, 0); border-radius: 3px}");
    ui->Slider_g->setStyleSheet("QSlider::handle:horizontal {background-color: rgb(0, 255, 0); border-radius: 3px}");
    ui->Slider_b->setStyleSheet("QSlider::handle:horizontal {background-color: rgb(0, 0, 255); border-radius: 3px}");
    ui->Slider_proz->setStyleSheet("QSlider::handle:horizontal {background-color: rgb(177, 177, 177); border-radius: 3px}");



    ui->widget->create_im(ui->widget->width(),ui->widget->height());
    ui->widget->im.fill(0);
}

Dialog_pixel::~Dialog_pixel()//деструктор
{
    delete ui;
}

void Dialog_pixel::setValue(my_pen n_pen)//устанавливаем значения
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


    QPainter painter(&ui->widget->im);
    QColor color;
    QBrush brush;
    color.setRgb(red,green,blue,alpha);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    ui->widget->im.fill(0);
    painter.drawRect(-1,-1,300,200);
    repaint();




}

void Dialog_pixel::on_Slider_proz_valueChanged(int value)//если измении ползунок прозрачность
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
    painter.drawRect(-1,-1,300,200);
    repaint();
}


void Dialog_pixel::on_Slider_b_valueChanged(int value)//если изменили ползунок синего цвета
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
    painter.drawRect(-1,-1,300,200);
    repaint();
}


void Dialog_pixel::on_Slider_g_valueChanged(int value)//если изменили ползунок зеленого цвета
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
    painter.drawRect(-1,-1,300,200);
    repaint();
}


void Dialog_pixel::on_Slider_r_valueChanged(int value)//если изменили ползунок красного цвета
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
    painter.drawRect(-1,-1,300,200);
    repaint();
}





void Dialog_pixel::on_pushButton_ok_clicked()
{
    red=ui->label_r_2->text().toInt();
    green=ui->label_g_2->text().toInt();
    blue=ui->label_b_2->text().toInt();
    alpha=ui->label_3->text().toInt();

    close();
}

