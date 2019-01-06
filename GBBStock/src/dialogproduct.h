#ifndef DIALOGPRODUCT_H
#define DIALOGPRODUCT_H

#include <QDialog>
#include <QCompleter>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>

#include "global.h"
#include "calculator.h"
#include "dbinterface.h"

namespace Ui {
class DialogProduct;
}

class DialogProduct : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProduct(QWidget *parent = 0);
    ~DialogProduct();

    void setProductInformation(const ProductInfo &info, DBInterface *dbi);
    ProductInfo getProductInfo() const {return productInfo;}

private slots:

    void on_pbAceptar_clicked();

    void on_pbCalcularCP_clicked();

    void on_pbCancelar_clicked();

    void on_pbCalcularCM_clicked();

private:
    Ui::DialogProduct *ui;
    DBInterface *db;
    ProductInfo productInfo;
    void showErrorMessage(const QString &err);

    void fillCompleter(QLineEdit *le, QString tableColumn);
};

#endif // DIALOGPRODUCT_H
