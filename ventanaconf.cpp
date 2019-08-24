#include "ventanaconf.h"
#include "ui_ventanaconf.h"
#include <QtSql>
#include <QSqlQuery>
#include <fstream>
#include <QMessageBox>
#include <QCryptographicHash>

using namespace std;

ventanaConf::ventanaConf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventanaConf)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password); //Ocultar la contraseña
    //Recoger datos
    recogerConf();
}

ventanaConf::~ventanaConf()
{
    delete ui;
}

struct
{
    ifstream usuario, contra, db, serv;
    string temp[4];
}archivo;

void ventanaConf::recogerConf()
{
    //PASO 1 - Recoger el usuario
    archivo.usuario.open("usuario/user.txt", ios::in);
    if(archivo.usuario.fail())
    {
        //No hace falta - TODO: Eliminar esta línea:
        //primerArranque();
        QMessageBox::information(this, "Error", "Ha habido un problema importante. El programa"
                                                " se cerrará");
        exit(0);
    }
    while(!archivo.usuario.eof())
    {
        getline(archivo.usuario, archivo.temp[0]);
    }
    archivo.usuario.close();
    //PASO 2 - Recoger la db
    archivo.db.open("usuario/db.txt", ios::in);
    while(!archivo.db.eof())
    {
        getline(archivo.db, archivo.temp[2]);
    }
    archivo.db.close();
    //PASO 3 - Recoger el servidor
    archivo.serv.open("usuario/serv.txt", ios::in);
    while(!archivo.serv.eof())
    {
        getline(archivo.serv, archivo.temp[3]);
    }
    archivo.serv.close();
    //PASO 4 - Recoger la contraseña
    archivo.contra.open("usuario/pass.txt", ios::in);
    while(!archivo.contra.eof())
    {
        getline(archivo.contra, archivo.temp[1]);
    }
    archivo.contra.close();
    //TODO - El proceso de haseho completo
}

void ventanaConf::on_pushButton_clicked()
{
    QSqlQuery query;
    query.exec("DROP DATABASE qt;");
    query.exec("CREATE DATABASE qt;");
    ofstream cuenta;
    cuenta.open("usuario/count.txt", ios::out);
    cuenta <<-1;
    cuenta.close();
    QMessageBox::information(this, "Información", "Datos borrados correctamente. La aplicación se cerrará.");
    exit(0);
}

void ventanaConf::on_pushButton_3_clicked()
{
    reject();
}

void ventanaConf::on_toolButton_clicked()
{
    ui->servidor->setText("localhost");
}

void ventanaConf::on_pushButton_2_clicked()
{
    on_toolButton_clicked();
    ui->usuario->setText("root");
    ui->password->setText("123456");
    ui->db->setText("qt");
}
