#include "dialogproduct.h"
#include "ui_dialogproduct.h"

DialogProduct::DialogProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProduct)
{
    ui->setupUi(this);
    productInfo[FLAG_ISNEW] = "true";
    ui->leError->setVisible(false);
}

void DialogProduct::setProductInformation(const ProductInfo &info, const QStringList &tipoProd, const QStringList &marcas){

    ui->cbTipoProd->addItem("Nuevo Tipo de Producto");
    for (qint32 i = 0; i < tipoProd.size(); i++){
        ui->cbTipoProd->addItem(tipoProd.at(i));
    }
    ui->cbTipoProd->setCurrentIndex(0);

    ui->cbMarca->addItem("Nueva Marca");
    for (qint32 i = 0; i < marcas.size(); i++){
        ui->cbMarca->addItem(marcas.at(i));
    }
    ui->cbMarca->setCurrentIndex(0);

    for (qint32 i = 0; i < tipoProd.size(); i++){
        if (tipoProd.at(i) == productInfo[TSTOCK_COL_TIPO_PROD]){
            ui->cbTipoProd->setCurrentIndex(i+1);
            break;
        }
    }

    for (qint32 i = 0; i < marcas.size(); i++){
        if (marcas.at(i) == productInfo[TSTOCK_COL_TIPO_PROD]){
            ui->cbTipoProd->setCurrentIndex(i+1);
            break;
        }
    }

    productInfo = info;
    productInfo[FLAG_ISNEW] = "false";

    // Loading the rest of the information
    ui->leCodigo->setText(productInfo[TSTOCK_COL_CODIGO]);
    ui->leCodigoAlt->setText(productInfo[TSTOCK_COL_COD_ALT]);
    ui->pteDesc->setPlainText(productInfo[TSTOCK_COL_DESC]);
    ui->leCosto->setText(productInfo[TSTOCK_COL_COST]);
    ui->leCostoP->setText(productInfo[TSTOCK_COL_COSTP]);
    ui->leCostoM->setText(productInfo[TSTOCK_COL_COSTM]);
    ui->leCantidadFrente->setText(productInfo[TSTOCK_COL_STOCK_F]);
    ui->leCantidadAtras->setText(productInfo[TSTOCK_COL_STOCK_D]);
    ui->leUbicacion->setText(productInfo[TSTOCK_COL_LOCAT]);
    ui->leColumna->setText(productInfo[TSTOCK_COL_COL]);
    ui->leEstante->setText(productInfo[TSTOCK_COL_ESTANTE]);
    ui->leEnvase->setText(productInfo[TSTOCK_COL_ENV]);
    ui->leMinStockDep->setText(productInfo[TSTOCK_COL_STOCK_MIN_D]);
    ui->leMinStockFrente->setText(productInfo[TSTOCK_COL_STOCK_MIN_F]);

}



DialogProduct::~DialogProduct()
{
    delete ui;
}

void DialogProduct::on_pbAceptar_clicked()
{

    // Verification. Mandatory stuff must be present.
    if (ui->leCodigo->text().isEmpty()){
        ui->leError->setText("El código de error no puede estar vacío");
        ui->leError->setVisible(true);
        return;
    }

    if ((ui->cbMarca->currentIndex() == 0) && ui->leMarca->text().isEmpty()){
        ui->leError->setText("El producto debe tener una marca");
        ui->leError->setVisible(true);
        return;
    }

    if ((ui->cbTipoProd->currentIndex() == 0) && ui->leTipoProd->text().isEmpty()){
        ui->leError->setText("El producto debe ser de algun tipo");
        ui->leError->setVisible(true);
        return;
    }

    if (ui->leCosto->text().isEmpty()) ui->leCosto->setText("0");


    productInfo[TSTOCK_COL_CODIGO] = ui->leCodigo->text();
    productInfo[TSTOCK_COL_COD_ALT] = ui->leCodigoAlt->text();
    productInfo[TSTOCK_COL_DESC] = ui->pteDesc->toPlainText();
    productInfo[TSTOCK_COL_COST] = ui->leCosto->text();
    productInfo[TSTOCK_COL_COSTP] = ui->leCostoP->text();
    productInfo[TSTOCK_COL_COSTM] = ui->leCostoM->text();
    productInfo[TSTOCK_COL_STOCK_F] = ui->leCantidadFrente->text();
    productInfo[TSTOCK_COL_STOCK_D] = ui->leCantidadAtras->text();
    productInfo[TSTOCK_COL_LOCAT] = ui->leUbicacion->text();
    productInfo[TSTOCK_COL_COL] = ui->leColumna->text();
    productInfo[TSTOCK_COL_ESTANTE] = ui->leEstante->text();
    productInfo[TSTOCK_COL_ENV] = ui->leEnvase->text();
    productInfo[TSTOCK_COL_STOCK_MIN_D] = ui->leMinStockDep->text();
    productInfo[TSTOCK_COL_STOCK_MIN_F] = ui->leMinStockFrente->text();

    if (ui->cbMarca->currentIndex() > 0) productInfo[TSTOCK_COL_MARCA] = ui->cbMarca->currentText();
    else productInfo[TSTOCK_COL_MARCA] = ui->leMarca->text();


    if (ui->cbTipoProd->currentIndex() > 0) productInfo[TSTOCK_COL_TIPO_PROD] = ui->cbTipoProd->currentText();
    else productInfo[TSTOCK_COL_TIPO_PROD] = ui->leTipoProd->text();

    this->accept();
}
