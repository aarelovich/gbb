#ifndef DIAGVENTA_H
#define DIAGVENTA_H

#include <QDialog>
#include <QMessageBox>
#include <QDir>
#include "dbinterface.h"

namespace Ui {
class DiagVenta;
}

class DiagVenta : public QDialog
{
    Q_OBJECT

public:
    explicit DiagVenta(QWidget *parent = 0);
    void setDBInterface(DBInterface *dbi) {db = dbi;}
    void setProductInfo(const ProductInfo &info);

    ~DiagVenta();

private slots:
    void on_spUnitsSold_valueChanged(int arg1);
    void notAPDF();

    void on_pbCancel_clicked();

    void on_pbOk_clicked();

    void on_cbPriceType_currentIndexChanged(int index);

private:
    Ui::DiagVenta *ui;
    DBInterface *db;
    ProductInfo pinfo;
};

#endif // DIAGVENTA_H
