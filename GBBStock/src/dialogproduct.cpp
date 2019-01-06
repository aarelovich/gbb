#include "dialogproduct.h"
#include "ui_dialogproduct.h"

DialogProduct::DialogProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProduct)
{
    ui->setupUi(this);
    ui->leError->setVisible(false);

    ui->leCosto->setValidator(new QDoubleValidator(0,1e9,4,this));
    ui->leCostoM->setValidator(new QDoubleValidator(0,1e9,4,this));
    ui->leCostoP->setValidator(new QDoubleValidator(0,1e9,4,this));
    ui->leColumna->setValidator(new QIntValidator(0,100,this));
    ui->leEstante->setValidator(new QIntValidator(0,100,this));

}

void DialogProduct::setProductInformation(const ProductInfo &info, DBInterface *dbi){

    db = dbi;
    productInfo = info;

    fillCompleter(ui->leTipoProd,TSTOCK_COL_TIPO_PROD);
    fillCompleter(ui->leMarca,TSTOCK_COL_MARCA);
    fillCompleter(ui->leCodigo,TSTOCK_COL_PRODUCTO);
    fillCompleter(ui->leEnvase,TSTOCK_COL_ENV);

    // Loading the rest of the information
    ui->leCodigo->setText(productInfo[TSTOCK_COL_PRODUCTO]);
    ui->leCodigoAlt->setText(productInfo[TSTOCK_COL_NOMBRE_ALT]);
    ui->leMarca->setText(productInfo[TSTOCK_COL_MARCA]);
    ui->leTipoProd->setText(productInfo[TSTOCK_COL_TIPO_PROD]);
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
    ui->leFormulaCM->setText(productInfo[TSTOCK_COL_FORMULA_M]);
    ui->leFormulaCP->setText(productInfo[TSTOCK_COL_FORMULA_P]);

}


void DialogProduct::fillCompleter(QLineEdit *le, QString tableColumn){

    QStringList cols;
    QStringList names;

    cols << tableColumn;
    if (!db->readFromDB(TABLE_STOCK,cols,"",true)){
        errorLog("Creating completer for " + tableColumn + " got: " + db->getError());
        return;
    }

    DBData data = db->getLastResult();
    for (qint32 i = 0; i < data.rows.size(); i++){
        if (data.rows.at(i).size() > 0){
            names << data.rows.at(i).first();
        }
    }

    QCompleter *completer = new QCompleter(names,this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    le->setCompleter(completer);

}

DialogProduct::~DialogProduct()
{
    delete ui;
}

void DialogProduct::on_pbAceptar_clicked()
{

    ui->leError->setVisible(false);

    // Verification. Mandatory stuff must be present.
    if (ui->leCodigo->text().isEmpty()){
        showErrorMessage("El código del producto no puede estar vacío");
        return;
    }

    if (ui->leMarca->text().isEmpty()){
        showErrorMessage("El producto debe tener una marca");
        return;
    }

    if (ui->leTipoProd->text().isEmpty()){
        showErrorMessage("El producto debe ser de algun tipo");
        return;
    }

    QString prodName = cleanUpUniquetName(ui->leCodigo->text());
    QString brand = cleanUpUniquetName(ui->leMarca->text());
    QString prodType = cleanUpUniquetName(ui->leTipoProd->text());
    QString recipient = cleanUpUniquetName(ui->leEnvase->text(),true);

    if (ui->leCosto->text().isEmpty()) ui->leCosto->setText("0");
    if (ui->leCostoP->text().isEmpty()) ui->leCostoP->setText(ui->leCosto->text());
    if (ui->leCostoM->text().isEmpty()) ui->leCostoM->setText(ui->leCosto->text());
    if (ui->leCantidadAtras->text().isEmpty()) ui->leCantidadAtras->setText("0");
    if (ui->leCantidadFrente->text().isEmpty()) ui->leCantidadFrente->setText("0");
    if (ui->leMinStockDep->text().isEmpty()) ui->leMinStockDep->setText("0");
    if (ui->leMinStockFrente->text().isEmpty()) ui->leMinStockFrente->setText("0");
    if (ui->leColumna->text().isEmpty()) ui->leColumna->setText("0");
    if (ui->leEstante->text().isEmpty()) ui->leEstante->setText("0");

    productInfo[TSTOCK_COL_PRODUCTO] = prodName;
    productInfo[TSTOCK_COL_NOMBRE_ALT] = ui->leCodigoAlt->text();
    productInfo[TSTOCK_COL_DESC] = ui->pteDesc->toPlainText();
    productInfo[TSTOCK_COL_COST] = ui->leCosto->text();
    productInfo[TSTOCK_COL_COSTP] = ui->leCostoP->text();
    productInfo[TSTOCK_COL_COSTM] = ui->leCostoM->text();
    productInfo[TSTOCK_COL_STOCK_F] = ui->leCantidadFrente->text();
    productInfo[TSTOCK_COL_STOCK_D] = ui->leCantidadAtras->text();
    productInfo[TSTOCK_COL_LOCAT] = ui->leUbicacion->text();
    productInfo[TSTOCK_COL_COL] = ui->leColumna->text();
    productInfo[TSTOCK_COL_ESTANTE] = ui->leEstante->text();
    productInfo[TSTOCK_COL_ENV] = recipient;
    productInfo[TSTOCK_COL_STOCK_MIN_D] = ui->leMinStockDep->text();
    productInfo[TSTOCK_COL_STOCK_MIN_F] = ui->leMinStockFrente->text();
    productInfo[TSTOCK_COL_MARCA] = brand;
    productInfo[TSTOCK_COL_TIPO_PROD] = prodType;
    productInfo[TSTOCK_COL_FORMULA_M] = ui->leFormulaCM->text();
    productInfo[TSTOCK_COL_FORMULA_P] = ui->leFormulaCP->text();

    // Checking if the item exists.
    QString condition = QString(TSTOCK_COL_MARCA) + "='" + brand + "' AND "
            + QString(TSTOCK_COL_PRODUCTO) + " = '" + prodName + "' AND "
            + QString(TSTOCK_COL_ENV) + " = '" + recipient + "' AND "
            + QString(TSTOCK_COL_TIPO_PROD) + " = '" + prodType + "'";

    QStringList cols;
    cols << TSTOCK_COL_KEYID;
    QString keyid = "-1";
    if (!db->readFromDB(TABLE_STOCK,cols,condition)){
        errorLog("Attempting to check if entry exists: " + db->getError());
        showErrorMessage("No se puede verificar la existencia del producto. Error de base de datos. No se realizan cambios");
        return;
    }

    if (db->getLastResult().rows.size() > 0){
        if (db->getLastResult().rows.first().size() > 0){
            keyid = db->getLastResult().rows.first().first();
        }
    }

    productInfo.remove(TSTOCK_COL_KEYID);
    cols.clear();
    cols = productInfo.keys();
    condition = QString(TSTOCK_COL_KEYID) + " = '" + keyid + "'";
    QStringList values;
    for (qint32 i = 0; i < cols.size(); i++){
        values << productInfo.value(cols.at(i));
    }

    QSet<QString> skipParenthesisCheck;
    skipParenthesisCheck << TSTOCK_COL_FORMULA_M << TSTOCK_COL_FORMULA_P;

    if (keyid == "-1"){
       // Product does nto exist. A new product will be inserted.
       if (!db->insertDB(TABLE_STOCK,cols,values,skipParenthesisCheck)){
           errorLog("Attempting to insert new product: " + db->getError());
           showErrorMessage("No se puede agregar nuevo producto. No se realizan cambios");
           return;
       }
    }
    else{
        if (!db->updateDB(TABLE_STOCK,cols,values,condition)){
            errorLog("Attempting to update existing product: " + db->getError());
            showErrorMessage("No se puede modificar producto existente. Error de base de datos. No se realizan cambios");
            return;
        }
    }

    this->accept();
}

void DialogProduct::on_pbCalcularCP_clicked()
{
    ui->leError->setVisible(false);
    if (ui->leCosto->text().isEmpty()){
        showErrorMessage("Debe ingresar el costo antes de realizar el cálculo");
        return;
    }
    QMap<QString,qreal> vars;
    vars["x"] = ui->leCosto->text().toDouble();
    Calculator calc;
    if (!calc.evaluateExpression(ui->leFormulaCP->text(),vars)){
        showErrorMessage("La formula del costo público está mal escrita. Por favor verifiquela");
        return;
    }
    else{
        ui->leCostoP->setText(QString::number(calc.getResult()));
    }
}


void DialogProduct::on_pbCalcularCM_clicked()
{
    ui->leError->setVisible(false);
    if (ui->leCosto->text().isEmpty()){
        showErrorMessage("Debe ingresar el costo antes de realizar el cálculo");
        return;
    }
    QMap<QString,qreal> vars;
    vars["x"] = ui->leCosto->text().toDouble();
    Calculator calc;
    if (!calc.evaluateExpression(ui->leFormulaCM->text(),vars)){
        showErrorMessage("La formula del costo mayorista está mal escrita. Por favor verifiquela");
        return;
    }
    else{
        ui->leCostoM->setText(QString::number(calc.getResult()));
    }
}

void DialogProduct::showErrorMessage(const QString &err){
    ui->leError->setVisible(true);
    ui->leError->setText("<html><head/><body><p><span style=' font-size:12pt; color:#aa0000;'>" + err + "</span></p></body></html>");
}

void DialogProduct::on_pbCancelar_clicked()
{
    this->reject();
}


void DialogProduct::on_pbEliminarRegistro_clicked()
{
    if (!productInfo.contains(TSTOCK_COL_KEYID)) return;
    int ans = QMessageBox::question(this,"Confirmación","Si elimina este producto, no se podrá a acceder a este registro nuevamente. Confirme que desea realizar la operación.",
                                    QMessageBox::Ok,QMessageBox::Cancel);
    if (ans == QMessageBox::Cancel) return;
    QStringList columns; columns << TSTOCK_COL_BORRADO;
    QStringList values; values << "1";
    QString condition = QString(TSTOCK_COL_KEYID) + " = '" + productInfo.value(TSTOCK_COL_KEYID) + "'";
    if (!db->updateDB(TABLE_STOCK,columns,values,condition)){
        errorLog("Intentando borrar registro: " + db->getError());
        showErrorMessage("No ha sido posible borrar el registro");
        return;
    }
    this->accept();
}
