#include "diagchangeinmultiplefields.h"
#include "ui_diagchangeinmultiplefields.h"

DiagChangeInMultipleFields::DiagChangeInMultipleFields(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagChangeInMultipleFields)
{
    ui->setupUi(this);
    ui->leValueDouble->setValidator(new QDoubleValidator(0,1e9,3,this));
    ui->leValueInt->setValidator(new QIntValidator(0,10000000,this));

    fieldsWithDoubleValidator << TSTOCK_COL_COST << TSTOCK_COL_COSTM << TSTOCK_COL_COSTP;
    fieldsWithIntValidator << TSTOCK_COL_COL << TSTOCK_COL_ESTANTE << TSTOCK_COL_STOCK_D << TSTOCK_COL_STOCK_F << TSTOCK_COL_STOCK_MIN_D << TSTOCK_COL_STOCK_MIN_F;

}

DiagChangeInMultipleFields::~DiagChangeInMultipleFields()
{
    delete ui;
}

QString DiagChangeInMultipleFields::getFormula() const {
    return ui->leFormula->text();
}

QString DiagChangeInMultipleFields::getTableColumn() const {
    return ui->cbCampo->currentData().toString();
}

QString DiagChangeInMultipleFields::getValue() const {
    if (!ui->leValueDouble->text().isEmpty()) return ui->leValueDouble->text();
    else if (!ui->leValueInt->text().isEmpty()) return ui->leValueInt->text();
    else return ui->leValueText->text();
}

void DiagChangeInMultipleFields::showEvent(QShowEvent *e){
    QDialog::showEvent(e);
    on_cbCampo_currentIndexChanged(0);
}

void DiagChangeInMultipleFields::setColumnsAndNames(const QMap<QString, QString> colsAndFields){

    QStringList keys = colsAndFields.keys();
    keys.removeAll(TSTOCK_COL_KEYID);
    ui->cbCampo->blockSignals(true);
    for (qint32 i = 0; i < keys.size(); i++){
        ui->cbCampo->addItem(colsAndFields.value(keys.at(i)),keys.at(i));
    }
    ui->cbCampo->blockSignals(false);
}

void DiagChangeInMultipleFields::on_cbCampo_currentIndexChanged(int index)
{
    Q_UNUSED(index)

    QString field = ui->cbCampo->currentData().toString();
    bool canUseFormula = true;

    ui->leFormula->clear();
    ui->leValueDouble->clear();
    ui->leValueInt->clear();
    ui->leValueText->clear();

    QLineEdit *selectedLe;
    if (fieldsWithDoubleValidator.contains(field)){
        ui->leValueDouble->setVisible(true);
        ui->leValueInt->setVisible(false);
        ui->leValueText->setVisible(false);
        selectedLe = ui->leValueDouble;
    }
    else if (fieldsWithIntValidator.contains(field)){
        ui->leValueDouble->setVisible(false);
        ui->leValueInt->setVisible(true);
        ui->leValueText->setVisible(false);
        selectedLe = ui->leValueInt;
    }
    else{
        ui->leValueDouble->setVisible(false);
        ui->leValueInt->setVisible(false);
        ui->leValueText->setVisible(true);
        selectedLe = ui->leValueText;
        canUseFormula = false;
    }

    selectedLe->setEnabled(true);

    if ((canUseFormula) && (ui->cbModType->currentIndex() > 0)){
        ui->leFormula->setEnabled(true);
        selectedLe->setEnabled(false);
    }
    else{
        ui->leFormula->setEnabled(false);
    }

}

void DiagChangeInMultipleFields::on_cbModType_currentIndexChanged(int index)
{
    on_cbCampo_currentIndexChanged(index);
}

void DiagChangeInMultipleFields::on_pbOk_clicked()
{
    // Checking that the formula is kosher....

    if (ui->cbModType->currentIndex() > 0){

        Calculator calc;
        QMap<QString,qreal> map;
        map["x"] = 1;

        if (!calc.evaluateExpression(ui->leFormula->text(),map)){
            QMessageBox::critical(this,"Fórmula inválida","La formula " + ui->leFormula->text() + " es incorrecta.\nPor favor verifíquela");
            return;
        }

    }

    this->accept();
}

void DiagChangeInMultipleFields::on_pbCancel_clicked()
{
    this->reject();
}
