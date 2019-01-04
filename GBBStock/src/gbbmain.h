#ifndef GBBMAIN_H
#define GBBMAIN_H

#include <QMainWindow>
#include <QMessageBox>

#include "dialogproduct.h"
#include "dbinterface.h"

namespace Ui {
class GBBMain;
}

class GBBMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit GBBMain(QWidget *parent = 0);
    ~GBBMain();

private slots:
    void on_actionAgregar_un_nuevo_producto_triggered();

private:
    Ui::GBBMain *ui;
    DBInterface db;


    // Auxiliary functions.
    void showError(const QString &error);

};

#endif // GBBMAIN_H
