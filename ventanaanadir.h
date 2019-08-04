#ifndef VENTANAANADIR_H
#define VENTANAANADIR_H

#include <QDialog>

namespace Ui {
class ventanaAnadir;
}

class ventanaAnadir : public QDialog
{
    Q_OBJECT

public:
    explicit ventanaAnadir(QWidget *parent = nullptr);
    ~ventanaAnadir();

private slots:
    void on_buttonBox_rejected();

private:
    Ui::ventanaAnadir *ui;
};

#endif // VENTANAANADIR_H
