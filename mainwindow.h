#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    struct Datos{
        QString nombre[100], matricula[100], hora[100], frases[100];
        int autorizacion[100];
        int count = -1;
    }dato;

    void recogerCount();

    void recoger(int count); //Del servidor

    void crearTabla(int count);

    void insertarDatos(QString nom, QString matr, QString hora, int autori, int count);

private slots:
    void on_pushButton_6_clicked();

    void conectar();

    void on_pushButton_2_clicked();

    void on_toolButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    enum Columnas{
        NOMBRE, MATRICULA, HORA, AUTORIZACION
    };
};

#endif // MAINWINDOW_H
