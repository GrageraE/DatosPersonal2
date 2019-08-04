#include "ventanaanadir.h"
#include "ui_ventanaanadir.h"
#include "mainwindow.h"

ventanaAnadir::ventanaAnadir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventanaAnadir)
{
    ui->setupUi(this);
}

ventanaAnadir::~ventanaAnadir()
{
    delete ui;
}

void ventanaAnadir::on_buttonBox_rejected()
{
    reject();
}
