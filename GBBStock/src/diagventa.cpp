#include "diagventa.h"
#include "ui_diagventa.h"

DiagVenta::DiagVenta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagVenta)
{
    ui->setupUi(this);
    connect(ui->leTicketPath,SIGNAL(wrongFileType()),this,SLOT(notAPDF()));
    ui->lePrice->setValidator(new QDoubleValidator(0,1e9,3,this));
    ui->dteSaleTime->setDateTime(QDateTime::currentDateTime());
}

void DiagVenta::notAPDF(){
    QMessageBox::critical(this,"Tipo de archivo equivocado","Se espera que la factura sea un PDF.\nEl archivo seleccionado no lo es.");
}

void DiagVenta::setProductInfo(const ProductInfo &info){
    pinfo = info;
    //<html><head/><body><p><span style=" font-size:12pt; font-weight:600;">Producto:</span><span style=" font-size:12pt;"> ELNOMBRE</span></p></body></html>
    QString baseHTML = "<html><head/><body><p><span style=' font-size:12pt; font-weight:600;'>___: </span><span style=' font-size:12pt;'>****</span></p></body></html>";

    QString pname;
    QString ptype;
    QString brand;
    QString env;

    pname = baseHTML;
    pname = pname.replace("___","Producto");
    pname = pname.replace("****",pinfo.value(TSTOCK_COL_PRODUCTO));

    ptype = baseHTML;
    ptype = ptype.replace("___","Tipo de Producto");
    ptype = ptype.replace("****",pinfo.value(TSTOCK_COL_TIPO_PROD));

    brand = baseHTML;
    brand = brand.replace("___","Marca");
    brand = brand.replace("****",pinfo.value(TSTOCK_COL_MARCA));

    env = baseHTML;
    env = env.replace("___","Envase");
    env = env.replace("****",pinfo.value(TSTOCK_COL_ENV));

    on_spUnitsSold_valueChanged(0);

    ui->labProdName->setText(pname);
    ui->labBrand->setText(brand);
    ui->labProdType->setText(ptype);
    ui->labRecipient->setText(env);
}

DiagVenta::~DiagVenta()
{
    delete ui;
}

void DiagVenta::on_cbPriceType_currentIndexChanged(int index)
{
    on_spUnitsSold_valueChanged(index);
}

void DiagVenta::on_spUnitsSold_valueChanged(int arg1)
{
    QString which;
    if (ui->cbPriceType->currentIndex() == 0) which = TSTOCK_COL_COSTP;
    else which = TSTOCK_COL_COSTM;
    ui->lePrice->setText(QString::number(pinfo.value(which).toDouble()*arg1));
}

void DiagVenta::on_pbCancel_clicked()
{
    this->reject();
}

void DiagVenta::on_pbOk_clicked()
{

    if (ui->lePrice->text().isEmpty()){
        QMessageBox::critical(this,"No hay un precio de venta","Por favor calcule o ingrese un precio de venta para continuar");
        return;
    }

    if (ui->leTicketPath->text().isEmpty()){
        int ans = QMessageBox::question(this,"Factura no presente","Es necesario asociar la venta a una factura\nEstá seguro que desea continuar",QMessageBox::Ok,QMessageBox::Cancel);
        if (ans == QMessageBox::Cancel) return;
    }

    qint32 stockF = pinfo.value(TSTOCK_COL_STOCK_F).toInt();
    qint32 stockD = pinfo.value(TSTOCK_COL_STOCK_D).toInt();

    if (ui->spUnitsSold->value() >  stockF){
        if (ui->spUnitsSold->value() > stockF + stockD){
            QMessageBox::warning(this,"Unidades vendidas mayores al stock total",
                                 "Las unidades que se venderán son mayores que el stock del frente mas el del depósito.\nAmbos valores se cambiarán a 0.",
                                 QMessageBox::Ok);
            pinfo[TSTOCK_COL_STOCK_D] = "0";
            pinfo[TSTOCK_COL_STOCK_F] = "0";

        }
        else{
            QMessageBox::warning(this,"Unidades vendidas mayores al stock al frente",
                                 "Las unidades que se venderán son mayores que el stock al frente del local.\nLas restantes se restarán del stock del depósito",
                                 QMessageBox::Ok);
            pinfo[TSTOCK_COL_STOCK_D] = QString::number(stockD - (ui->spUnitsSold->value() - stockF));
            pinfo[TSTOCK_COL_STOCK_F] = "0";


        }
    }
    else{
        pinfo[TSTOCK_COL_STOCK_F] = QString::number(stockF - ui->spUnitsSold->value());
    }

    // Updating the stock
    QStringList columns; columns << TSTOCK_COL_STOCK_F << TSTOCK_COL_STOCK_D;
    QStringList values; values << pinfo.value(TSTOCK_COL_STOCK_F) << pinfo.value(TSTOCK_COL_STOCK_D);
    QString condition = QString(TSTOCK_COL_KEYID) + " = '" + pinfo.value(TSTOCK_COL_KEYID) + "'";

    if (!db->updateDB(TABLE_STOCK,columns,values,condition)){
        errorLog("Updating stock: " + db->getError());
        QMessageBox::critical(this,"Error en la base de datos","No se pudo actualizar el stock o registrar la venta");
        return;
    }

    // Moving the file to the local folder
    // Getting the number;

    QString ticketFileName = "";
    QString copyPath = "";
    if (!ui->leTicketPath->text().isEmpty()){
        QDir dir(DIR_TICKETS);
        uint count = 0;
        if (!dir.exists()){
            QDir(".").mkdir(DIR_TICKETS);
        }
        else{
            dir.setFilter(QDir::NoDotAndDotDot);
            count = dir.count();
        }

        // Generating the file name.
        ticketFileName = QString::number(count);
        while (ticketFileName.size() < 10) ticketFileName = "0" + ticketFileName;
        ticketFileName = ticketFileName + "_" + QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm");
        ticketFileName = ticketFileName;

        // Copying the file.
        copyPath = QString(DIR_TICKETS) + "/" + ticketFileName  + ".pdf";
        QFile::copy(ui->leTicketPath->text(),copyPath);
    }

    // Registering the sale.
    columns.clear();
    values.clear();
    columns << TVENTAS_COL_FECHA << TVENTAS_COL_PDFFAC << TVENTAS_COL_PROD << TVENTAS_COL_PRECIO << TVENTAS_COL_NOTA << TVENTAS_COL_VENDIDAS;
    values << ui->dteSaleTime->dateTime().toString("yyyy-MM-dd hh:mm:ss") << ticketFileName << pinfo.value(TSTOCK_COL_KEYID) << ui->lePrice->text() << ui->pteNota->toPlainText()
           << QString::number(ui->spUnitsSold->value());


    if (!db->insertDB(TABLE_VENTAS,columns,values)){
        errorLog("Inseriting a new sale: " + db->getError());
        QMessageBox::critical(this,"Error en la base de datos","No se pudo registrar la venta");
        return;
    }

    if (!QFile(copyPath).exists() && !copyPath.isEmpty()){
        QMessageBox::warning(this,"No se guardo la factura","No se pudo copiar el archivo de factura al directorio local pero la base de datos fue actualizado con éxito");
    }

    this->accept();
}

