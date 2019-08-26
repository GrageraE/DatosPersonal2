#include "ventanaconf.h"
#include "ui_ventanaconf.h"
#include <QtSql>
#include <QSqlQuery>
#include <fstream>
#include <QMessageBox>
using namespace std;

ventanaConf::ventanaConf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventanaConf)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password); //Ocultar la contraseña
    //Recoger datos
    if(!recogerConf())
    {
        primerArrnque();
    }
}

ventanaConf::~ventanaConf()
{
    delete ui;
}

bool ventanaConf::recogerConf()
{
    //PASO 1 - Recoger el usuario
    archivo.usuario.open("usuario/user.txt", ios::in);
    if(archivo.usuario.fail())
    {
        QMessageBox::information(this, "Error", "Ha habido un problema importante. El programa"
                                                " se cerrará");
        return false;
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
    //TODO - El proceso de encriptación completo
    return true;
}

void ventanaConf::primerArrnque()
{
    QMessageBox::information(this, "Información", "Primer arranque: se escribirán los datos básicos para "
                                                  "usar la aplicación. Podrás cambiarlos desde la "
                                                  "configuración");
    ofstream usuario, contra, db, serv;
    usuario.open("usuario/user.txt", ios::out);
    if(usuario.fail())
    {
        QMessageBox::information(this, "Error", "Ha ocurrido un error importante. La app "
                                                "se cerrará");
        exit(1);
    }
    usuario <<"root";
    usuario.close();
    contra.open("usuario/pass.txt", ios::out);
    contra <<"123456";
    contra.close();
    db.open("usuario/db.txt", ios::out);
    db <<"qt";
    db.close();
    serv.open("usuario/serv.txt", ios::out);
    serv <<"localhost";
    serv.close();
    QMessageBox::information(this, "Información", "Primer arranque completado. Archivos escritos "
                                                  "correctamente.");
    return;
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

void ventanaConf::on_pushButton_4_clicked()
{
    QString usuario, contra, serv, db;
    usuario = ui->usuario->text();
    contra = ui->password->text();
    serv = ui->servidor->text();
    db = ui->db->text();
    ofstream user, pass, host, database;
    user.open("usuario/user.txt", ios::out);
    if(user.fail())
    {
        QMessageBox::information(this, "Error", "Ha ocurrido un error al guardar la configuración");
        reject();
    }
    user <<usuario.toStdString();
    user.close();
    pass.open("usuario/pass.txt", ios::out);
    pass <<contra.toStdString();
    pass.close();
    host.open("usuario/serv.txt", ios::out);
    host <<serv.toStdString();
    host.close();
    database.open("usuario/db.txt", ios::out);
    database <<db.toStdString();
    database.close();
    QMessageBox::information(this, "Información", "Configuración guardada");
    return;
}
