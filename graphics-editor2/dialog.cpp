#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setValue(my_pen n_pen)
{
    my_style=n_pen.GetStyle();
    n_pen.GetColor(alpha,red,green,blue);

    ui->lineEdit_r->setText(QString::number(red));
    ui->lineEdit_g->setText(QString::number(green));
    ui->lineEdit_b->setText(QString::number(blue));

    ui->comboBox_penStyle->setVisible(StyleVisible);
    ui->label_style->setVisible(StyleVisible);
    ui->spinBox->setVisible(StyleVisible);
    ui->label->setVisible(StyleVisible);
    ui->comboBox_penStyle->setCurrentIndex(my_style);
}

void Dialog::setStyleVisible(bool fl)
{
    StyleVisible=fl;
}

void Dialog::on_buttonBox_accepted()
{
    int r,g,b,n_s;

    red=ui->lineEdit_r->text().toInt();
    green=ui->lineEdit_g->text().toInt();
    blue=ui->lineEdit_b->text().toInt();

}




