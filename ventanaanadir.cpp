#include "ventanaanadir.h"
#include "ui_ventanaanadir.h"
#include "mainwindow.h"
#include <fstream>
#include <string>
#include <QMessageBox>

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

void ventanaAnadir::on_buttonBox_accepted()
{
    //PASO 1 - Guardarlos en la db
    MainWindow mainwindow;
    QString nombre = ui->nombre->text();
    QString matricula = ui->matricula->text();
    QString hora = ui->hora->text();
    int autorizacion;
    if(ui->checkBox->isChecked())
        autorizacion = 1;
    else
        autorizacion = 0;
    //PASO 2 - Isertar datos al servidor
    mainwindow.insertarDatos(nombre, matricula, hora, autorizacion, mainwindow.dato.count+1);
    //PASO 3 - Mostrarlos en la tabla
    mainwindow.recoger(mainwindow.dato.count+1);
    //PASO 4 - Guardar el count
    mainwindow.dato.count++;
    std::system("MKDIR usuario");
    std::ofstream cuenta;
    cuenta.open("usuario/count.txt", std::ios::out);
    if(cuenta.fail())
    {
        QMessageBox::information(this, "Error", "Ha ocurrido un error al crear el fichero");
        return;
    }
    cuenta <<mainwindow.dato.count;
    cuenta.close();
    reject();
}
