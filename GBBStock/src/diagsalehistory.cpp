#include "diagsalehistory.h"
#include "ui_diagsalehistory.h"

DiagSaleHistory::DiagSaleHistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagSaleHistory)
{
    ui->setupUi(this);
    QDateTime now = QDateTime::currentDateTime();
    ui->dteEnd->setDateTime(now);
    ui->dteStart->setDateTime(now.addMonths(-1));

    ui->twSearchResults->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->twSearchResults,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(openPDF(int,int)));
    connect(ui->twSearchResults,SIGNAL(cellClicked(int,int)),this,SLOT(showNote(int,int)));

}

DiagSaleHistory::~DiagSaleHistory()
{
    delete ui;
}

void DiagSaleHistory::showEvent(QShowEvent *e){
    QDialog::showEvent(e);
}

void DiagSaleHistory::on_leSearch_returnPressed()
{
    QStringList productColumnsToSearch;
    QStringList productColumnsOfInterst;

    productSearchResults.clear();

    productColumnsToSearch << TSTOCK_COL_PRODUCTO << TSTOCK_COL_MARCA << TSTOCK_COL_ENV << TSTOCK_COL_TIPO_PROD;
    productColumnsOfInterst  << TSTOCK_COL_PRODUCTO << TSTOCK_COL_MARCA << TSTOCK_COL_ENV << TSTOCK_COL_TIPO_PROD << TSTOCK_COL_KEYID;

    // Searching the keyids of the prodcts that match the search string.
    QString condition;
    QStringList temp;
    for (qint32 i = 0; i < productColumnsToSearch.size(); i++){
        temp << "(" + productColumnsToSearch.at(i) + " LIKE '%" + ui->leSearch->text() + "%')";
    }
    condition = temp.join(" OR ");
    if (!db->readFromDB(TABLE_STOCK,productColumnsOfInterst,condition)){
        errorLog("Searching products for sale: " + db->getError());
        QMessageBox::critical(this,"Error buscando productos","No se puede realizar la búsqueda",QMessageBox::Ok);
        return;
    }

    DBData dbans = db->getLastResult();
    QStringList keyidsToSearch;

    for (qint32 i = 0; i < dbans.rows.size(); i++){
        ProductInfo info;
        for (qint32 j = 0; j < dbans.rows.at(i).size(); j++){
            info[productColumnsOfInterst.at(j)] = dbans.rows.at(i).at(j);
        }
        keyidsToSearch << info.value(TSTOCK_COL_KEYID);
        productSearchResults[info.value(TSTOCK_COL_KEYID)] = info;
    }

    // Now searching the actual sales table.
    QStringList salesColumnsOfInterest;
    salesColumnsOfInterest << TVENTAS_COL_FECHA << TVENTAS_COL_NOTA << TVENTAS_COL_PDFFAC << TVENTAS_COL_PRECIO
                           << TVENTAS_COL_PROD  << TVENTAS_COL_VENDIDAS;
    condition = "(" + QString(TVENTAS_COL_FECHA)  + " BETWEEN '" + ui->dteStart->dateTime().toString("yyyy-MM-dd hh:mm")
                                                     + "' AND '" + ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm") + "')";
    condition = condition + " AND " + QString(TVENTAS_COL_PROD) + " IN ('" + keyidsToSearch.join("', '") + "')";

    if (!db->readFromDB(TABLE_VENTAS,salesColumnsOfInterest,condition)){
        errorLog("Searching sales: " + db->getError());
        QMessageBox::critical(this,"Error buscando ventas","No se puede realizar la búsqueda",QMessageBox::Ok);
        return;
    }

    dbans = db->getLastResult();
    salesSearchResult.clear();

    for (qint32 i = 0; i < dbans.rows.size(); i++){
        ProductInfo info;
        for (qint32 j = 0; j < dbans.rows.at(i).size(); j++){
            info[salesColumnsOfInterest.at(j)] = dbans.rows.at(i).at(j);
        }
        salesSearchResult << info;
    }

    // Updating the table widget.
    QStringList headers; headers << "Producto" << "Marca" << "Tipo" << "Envase" << "Fecha" << "Unidades" << "Precio";
    ui->twSearchResults->blockSignals(true);
    ui->twSearchResults->clear();
    ui->twSearchResults->setRowCount(salesSearchResult.size());
    ui->twSearchResults->setColumnCount(headers.size());
    ui->twSearchResults->setHorizontalHeaderLabels(headers);

    for (qint32 i = 0; i < salesSearchResult.size(); i++){

        QTableWidgetItem *item;
        ProductInfo info = productSearchResults.value(salesSearchResult.at(i).value(TVENTAS_COL_PROD));

        item = new QTableWidgetItem(info.value(TSTOCK_COL_PRODUCTO));
        item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
        ui->twSearchResults->setItem(i,0,item);

        item = new QTableWidgetItem(info.value(TSTOCK_COL_MARCA));
        item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
        ui->twSearchResults->setItem(i,1,item);

        item = new QTableWidgetItem(info.value(TSTOCK_COL_TIPO_PROD));
        item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
        ui->twSearchResults->setItem(i,2,item);

        item = new QTableWidgetItem(info.value(TSTOCK_COL_ENV));
        item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
        ui->twSearchResults->setItem(i,3,item);

        item = new QTableWidgetItem(dbDateToShowDate(salesSearchResult.at(i).value(TVENTAS_COL_FECHA)));
        item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
        ui->twSearchResults->setItem(i,4,item);

        item = new QTableWidgetItem(salesSearchResult.at(i).value(TVENTAS_COL_VENDIDAS));
        item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
        ui->twSearchResults->setItem(i,5,item);

        item = new QTableWidgetItem(salesSearchResult.at(i).value(TVENTAS_COL_PRECIO));
        item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
        ui->twSearchResults->setItem(i,6,item);


    }

    ui->twSearchResults->blockSignals(false);

}

QString DiagSaleHistory::dbDateToShowDate(const QString &dbdate){

    QStringList parts = dbdate.split("T");
    if (parts.size() != 2) return dbdate;

    QString date = parts.first();
    QString time = parts.last();

    parts = date.split("-");
    if (parts.size() != 3) return date + " " + time;
    date = parts.at(0) + "/" + parts.at(1) + "/" + parts.at(2);

    parts = time.split(":");
    if (parts.size() != 3) return date + " " + time;
    time = parts.at(0) + ":" + parts.at(1) + ":" + parts.at(2);

    return date + " " + time;
}

void DiagSaleHistory::on_pbButton_clicked()
{
    on_leSearch_returnPressed();
}


void DiagSaleHistory::openPDF(int row, int col){
    Q_UNUSED(col);
    if (row >= salesSearchResult.size()) return;
    QString filecode = salesSearchResult.at(row).value(TVENTAS_COL_PDFFAC);
    if (filecode.isEmpty()){
        QMessageBox::information(this,"Factura no disponible","No se ha anexado una factura a esta operación",QMessageBox::Ok);
        return;
    }
    QString fileName = QString(DIR_TICKETS) + "/" + filecode + ".pdf";
    QUrl uri = QUrl::fromLocalFile(fileName);
    QDesktopServices::openUrl(uri);
}

void DiagSaleHistory::showNote(int row, int col){
    Q_UNUSED(col);
    ui->plainTextEdit->setPlainText("");
    if (row >= salesSearchResult.size()) return;
    ui->plainTextEdit->setPlainText(salesSearchResult.at(row).value(TVENTAS_COL_NOTA));
}
