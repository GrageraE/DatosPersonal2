#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <string>
//Sql
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
//Ventanas
#include <ventanaanadir.h>

using namespace std;

/*
struct Datos{
    QString nombre[100], matricula[100], hora[100];
    int autorizacion[100];
    int count = -1;
}dato;
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Configurar columnas
    ui->tableWidget->setColumnCount(4);
    QStringList columnas;
    columnas <<"Nombre" <<"Matrícula" <<"Hora" <<"Autorización";
    ui->tableWidget->setHorizontalHeaderLabels(columnas);
    //Conectar a MySql
    conectar();
    recogerCount();
    recoger(dato.count);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_6_clicked()
{
    exit(0);
}

void MainWindow::conectar()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("qt");
    if(!db.open())
    {
        QMessageBox::information(this, "Error", db.lastError().text());
        return;
    }
    QMessageBox::information(this, "Información", "Se ha conectado a MySql");
    return;
}

void MainWindow::recoger(int count) //Del servidor
{
    QSqlQuery query;
    int i = 0;
    while(i<=count)
    {
        query.exec("SELECT * FROM person" + QString::number(i) + ";");
        while(query.next())
        {
            dato.nombre[i] = query.value(0).toString();
            dato.matricula[i] = query.value(1).toString();
            dato.hora[i] = query.value(2).toString();
            dato.autorizacion[i] = query.value(3).toInt();
        }
        i++;
    }
    i=0;
    while(i<=count)
    {
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, NOMBRE,
                                 new QTableWidgetItem(dato.nombre[i]));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, MATRICULA,
                                 new QTableWidgetItem(dato.matricula[i]));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, HORA,
                                 new QTableWidgetItem(dato.hora[i]));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, AUTORIZACION,
                                 new QTableWidgetItem(dato.autorizacion[i]));
        i++;
    }
}

void MainWindow::crearTabla(int count)
{
    QSqlQuery query;
    QString comando = "CREATE TABLE person" + QString::number(count) + "(nombre varchar(100), "
                                                                       "matricula varchar(100), "
                                                                       "hora varchar(50), "
                                                                       "autorizacion int);";
    if(!query.exec(comando))
    {
        QMessageBox::information(this, "Error", query.lastError().text());
        return;
    }
    QMessageBox::information(this, "Información", "Tabla creada con éxito");
    return;
}

void MainWindow::insertarDatos(QString nom, QString matr, QString hora, int autori, int count) //Al servidor
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("qt");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("123456");
    db.setPort(3306);
    if(!db.tables().contains("person" + QString::number(count)))
    {
        crearTabla(count);
    }
    QSqlQuery query;
    QString cmd = "INSERT INTO person" + QString::number(count) + "(nombre varchar(100),"
                                                                  "matricula varchar(100),"
                                                                  "hora varchar(50),"
                                                                  "autorizacion int)";

    cmd += " VALUES('" + nom + "','" + matr + "','" + hora + "'," + QString::number(autori) + ");";

    QMessageBox::information(this, "Sql", cmd);
    if(!query.exec(cmd))
    {
        QMessageBox::information(this, "Error", query.lastError().text());
        return;
    }
    QMessageBox::information(this, "Información", "Se ha insertado los datos correctamente");
}

void MainWindow::recogerCount()
{
    ifstream cuenta;
    cuenta.open("usuario/count.txt", ios::in);
    if(cuenta.fail())
    {
        QMessageBox::information(this, "Información", "Los archivos de usuario se crearán al añadir personal.");
        return;
    }
    string temp;
    while (!cuenta.eof()) {
        getline(cuenta, temp);
    }
    cuenta.close();
    dato.count = stoi(temp);
}

void MainWindow::on_pushButton_2_clicked() //Ventanaañadir
{
    ventanaAnadir ventanaanadir;
    ventanaanadir.setModal(true);
    ventanaanadir.exec();
}
