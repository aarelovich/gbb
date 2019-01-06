#include "diagcsvimport.h"
#include "ui_diagcsvimport.h"

DiagCSVImport::DiagCSVImport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagCSVImport)
{
    ui->setupUi(this);

    // Connection for the update
    connect(&csvImporter,SIGNAL(updateProgress(qint32)),ui->progressBar,SLOT(setValue(int)));

    // Connection to know when a csv thread is done.
    connect(&csvImporter,SIGNAL(finished()),this,SLOT(on_csvThreadDone()));

    ui->twNewProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twUpdates->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void DiagCSVImport::showEvent(QShowEvent *e){
    QDialog::showEvent(e);
    csvImporter.setPrepareMode(true);
    ui->labStatus->setText("Espere mientras se analiza el CSV, por favor ....");

    ui->twNewProducts->setEnabled(false);
    ui->twUpdates->setEnabled(false);
    ui->pbAplicarCambios->setEnabled(false);
    ui->pbCancelar->setEnabled(false);

    csvImporter.start();
}

void DiagCSVImport::on_csvThreadDone(){

    ui->twNewProducts->setEnabled(true);
    ui->twUpdates->setEnabled(true);
    ui->pbAplicarCambios->setEnabled(true);
    ui->pbCancelar->setEnabled(true);

    if (!csvImporter.getPrepareMode()){
        ui->labStatus->setText("Proceso finalizado");
        if (!csvImporter.getError().isEmpty())
            QMessageBox::critical(this,"Error de importación","Se ha encontrado el siguiente error en el proceso de importación:\n" + csvImporter.getError());
        else
            QMessageBox::information(this,"Importación finalizada","El proceso de importación ha finalizado correctamente");
        this->accept();
        return;
    }
    else{
        if (!csvImporter.getError().isEmpty()){
            QMessageBox::critical(this,"Error de analisis","Se ha encontrado el siguiente error en el proceso de análisis:\n" + csvImporter.getError());
            this->reject();
            return;
        }
        ui->labStatus->setText("Por favor revise los cambios cuidadosamente antes de seguir...");
        QList<ProductInfo> list = csvImporter.getProductList(false);
        fillWidgetTables(ui->twNewProducts,list);
        list = csvImporter.getProductList(true);
        fillWidgetTables(ui->twUpdates,list);
    }

}

void DiagCSVImport::fillWidgetTables(QTableWidget *tw, const QList<ProductInfo> &list){
    // This was prepare mode and I need to fill the table widgets.
    QStringList headers; headers << "Producto" << "Marca" << "Tipo" << "Costo" << "Envase";
    QStringList tableColumnsForHeaders; tableColumnsForHeaders << TSTOCK_COL_PRODUCTO << TSTOCK_COL_MARCA << TSTOCK_COL_TIPO_PROD << TSTOCK_COL_COST << TSTOCK_COL_ENV;

    // Filling the new products
    tw->setRowCount(list.size());
    tw->setColumnCount(headers.size());
    tw->setHorizontalHeaderLabels(headers);

    for (qint32 i = 0; i < list.size(); i++){
        for (qint32 j = 0; j < tableColumnsForHeaders.size(); j++){
            QTableWidgetItem *item = new QTableWidgetItem(list.at(i).value(tableColumnsForHeaders.at(j)));
            tw->setItem(i,j,item);
            item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
        }
    }

}

DiagCSVImport::~DiagCSVImport()
{
    delete ui;
}

void DiagCSVImport::on_pbAplicarCambios_clicked()
{
    csvImporter.setPrepareMode(false);
    ui->labStatus->setText("Espere mientra se guardan los cambios en la base de datos, por favor ....");

    ui->twNewProducts->setEnabled(false);
    ui->twUpdates->setEnabled(false);
    ui->pbAplicarCambios->setEnabled(false);
    ui->pbCancelar->setEnabled(false);

    csvImporter.start();

}

void DiagCSVImport::on_pbCancelar_clicked()
{
    this->reject();
}
