#ifndef VENTANACONF_H
#define VENTANACONF_H

#include <QDialog>

namespace Ui {
class ventanaConf;
}

class ventanaConf : public QDialog
{
    Q_OBJECT

public:
    explicit ventanaConf(QWidget *parent = nullptr);
    ~ventanaConf();

    void recogerConf();

    // void primerArranque();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_toolButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ventanaConf *ui;
};

#endif // VENTANACONF_H
