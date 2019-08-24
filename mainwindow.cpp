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
#include <ventanaconf.h>

using namespace std;

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
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //Desactivar edición
    ui->tableWidget->setUpdatesEnabled(true);
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
    ui->label->setText("Se ha conectado a MySql");
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
        if(dato.autorizacion[i]==0)
        {
            dato.frases[i] = "No autorizado";
        }
        else{
            dato.frases[i] = "Autorizado";
        }
        i++;
    }
    i=0;
    while(i<=count)
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, NOMBRE,
                                 new QTableWidgetItem(dato.nombre[i]));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, MATRICULA,
                                 new QTableWidgetItem(dato.matricula[i]));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, HORA,
                                 new QTableWidgetItem(dato.hora[i]));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, AUTORIZACION,
                                 new QTableWidgetItem(dato.frases[i]));
        i++;
    }
    ui->tableWidget->repaint();
}

void MainWindow::crearTabla(int count)
{
    QSqlQuery query;
    QString comando = "CREATE TABLE person" + QString::number(count) + "(nombre varchar(100), "
                                                                       "matricula varchar(100), "
                                                                       "hora varchar(100), "
                                                                       "autorizacion int);";
    if(!query.exec(comando))
    {
        QMessageBox::information(this, "Error", query.lastError().text());
        return;
    }
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
    db.open();
    if(!db.tables().contains("person" + QString::number(count)))
    {
        crearTabla(count);
    }
    QSqlQuery query;
    QString cmd = "INSERT INTO person" + QString::number(count) + "(nombre,"
                                                                  "matricula,"
                                                                  "hora,"
                                                                  "autorizacion)";

    cmd += " VALUES ('" + nom + "','" + matr + "','" + hora + "'," + QString::number(autori) + ");";

    if(!query.exec(cmd))
    {
        QMessageBox::information(this, "Error", query.lastError().text());
        return;
    }
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

void MainWindow::on_toolButton_clicked()
{
    ofstream cuenta;
    cuenta.open("usuario/count.txt", std::ios::out);
    cuenta <<-1;
    cuenta.close();
    QMessageBox::information(this, "Información", "Se ha borrado el archivo correctamente."
                                                  "Se procederá a reiniciar el programa.");
    exit(0);
}

void MainWindow::on_pushButton_clicked()
{
    int fila = ui->tableWidget->currentRow();
    QSqlQuery query;
    query.exec("DROP TABLE person" + QString::number(fila) + ";"); //PASO 1 - Eliminar del servidor
    ui->tableWidget->removeRow(fila); //PASO 2 - Eliminar la fila
    ui->label->setText("La columna " + QString::number(fila+1) + " se ha eliminado correctamente");
    //PASO 3 - Revertir la cuenta
    std::ofstream cuenta;
    dato.count--;
    cuenta.open("usuario/count.txt", std::ios::out);
    cuenta <<dato.count;
    cuenta.close();
    return;
}

void MainWindow::on_pushButton_5_clicked()
{
    ventanaConf ventanaconf;
    ventanaconf.setModal(true);
    ventanaconf.exec();
}
