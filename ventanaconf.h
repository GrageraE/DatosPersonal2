#ifndef VENTANACONF_H
#define VENTANACONF_H

#include <QDialog>
#include <fstream>
#include <string>
using namespace std;

namespace Ui {
class ventanaConf;
}

class ventanaConf : public QDialog
{
    Q_OBJECT

public:
    explicit ventanaConf(QWidget *parent = nullptr);
    ~ventanaConf();

    struct
    {
        ifstream usuario, contra, db, serv;
        string temp[4]; //usuario, contraseña, db, servidor
    }archivo;

    bool recogerConf();

    void primerArrnque();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_toolButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ventanaConf *ui;
};

#endif // VENTANACONF_H
