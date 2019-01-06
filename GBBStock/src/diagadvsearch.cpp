#include "diagadvsearch.h"
#include "ui_diagadvsearch.h"

DiagAdvSearch::DiagAdvSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::diagadvsearch)
{
    ui->setupUi(this);
}

void DiagAdvSearch::setActiveColumns(const QStringList &searchCols){

    QMap<QString,QString> nameAndData;
    nameAndData[TSTOCK_COL_PRODUCTO]   = "Producto";
    nameAndData[TSTOCK_COL_NOMBRE_ALT] = "Nombre alternativo";
    nameAndData[TSTOCK_COL_DESC]   = "Descripción";
    nameAndData[TSTOCK_COL_LOCAT]   = "Ubicación";
    nameAndData[TSTOCK_COL_COL]   = "Columna";
    nameAndData[TSTOCK_COL_ESTANTE]   = "Estante";
    nameAndData[TSTOCK_COL_TIPO_PROD]   = "Tipo de Producto";
    nameAndData[TSTOCK_COL_ENV]   = "Envase";
    nameAndData[TSTOCK_COL_MARCA]   = "Marca";
    nameAndData[TSTOCK_COL_FORMULA_M]   = "Forumula de Mayorista";
    nameAndData[TSTOCK_COL_FORMULA_P]   = "Formula de Producto";

    QStringList keys = nameAndData.keys();

    ui->listWidget->clear();

    for (qint32 i = 0; i < keys.size(); i++){
        QListWidgetItem *item = new QListWidgetItem(nameAndData.value(keys.at(i)),ui->listWidget);
        if (searchCols.contains(keys.at(i))) item->setCheckState(Qt::Checked);
        else item->setCheckState(Qt::Unchecked);
        item->setData(DATA_ROLE_COL_NAME,keys.at(i));
    }

}

QStringList DiagAdvSearch::getActiveColumns(){
    QStringList ans;
    for (qint32 i = 0; i < ui->listWidget->count(); i++){
        if (ui->listWidget->item(i)->checkState() == Qt::Checked){
            ans << ui->listWidget->item(i)->data(DATA_ROLE_COL_NAME).toString();
        }
    }
    return ans;
}

DiagAdvSearch::~DiagAdvSearch()
{
    delete ui;
}

void DiagAdvSearch::on_pbSellAll_clicked()
{
    for (qint32 i = 0; i < ui->listWidget->count(); i++){
        ui->listWidget->item(i)->setCheckState(Qt::Checked);
    }
}

void DiagAdvSearch::on_pbSellNone_clicked()
{
    for (qint32 i = 0; i < ui->listWidget->count(); i++){
        ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
    }

}
