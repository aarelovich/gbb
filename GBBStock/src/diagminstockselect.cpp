#include "diagminstockselect.h"
#include "ui_diagminstockselect.h"

DiagMinStockSelect::DiagMinStockSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagMinStockSelect)
{
    ui->setupUi(this);
}

DiagMinStockSelect::~DiagMinStockSelect()
{
    delete ui;
}

void DiagMinStockSelect::on_pbOk_clicked()
{
    condition = "";
    switch ((ui->comboBox->currentIndex())) {
    case 0:
        condition = QString(TSTOCK_COL_STOCK_F) + "<=" + QString(TSTOCK_COL_STOCK_MIN_F);
        break;
    case 1:
        condition = QString(TSTOCK_COL_STOCK_D) + "<=" + QString(TSTOCK_COL_STOCK_MIN_D);
        break;
    case 2:
        condition = "(" + QString(TSTOCK_COL_STOCK_F) + "<=" + QString(TSTOCK_COL_STOCK_MIN_F) + ") OR (" +
                     QString(TSTOCK_COL_STOCK_D) + "<=" + QString(TSTOCK_COL_STOCK_MIN_D) + ")";
        break;
    }
    this->accept();
}

void DiagMinStockSelect::on_pbCancel_clicked()
{
    this->reject();
}
