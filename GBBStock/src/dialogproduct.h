#ifndef DIALOGPRODUCT_H
#define DIALOGPRODUCT_H

#include <QDialog>
#include "global.h"
#include "calculatorparser.h"

namespace Ui {
class DialogProduct;
}

class DialogProduct : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProduct(QWidget *parent = 0);
    ~DialogProduct();

    void setProductInformation(const ProductInfo &info, const QStringList &tipoProd, const QStringList &marcas);
    ProductInfo getProductInfo() const {return productInfo;}

private slots:

    void on_pbAceptar_clicked();

private:
    Ui::DialogProduct *ui;
    ProductInfo productInfo;
};

#endif // DIALOGPRODUCT_H
