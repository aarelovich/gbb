#include "diagwaitdboperation.h"
#include "ui_diagwaitdbrestore.h"

DiagWaitDBOperation::DiagWaitDBOperation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagWaitDBRestore)
{
    ui->setupUi(this);
    connect(&worker,SIGNAL(finished()),this,SLOT(accept()));
}

void DiagWaitDBOperation::showEvent(QShowEvent *e){
    QDialog::showEvent(e);
    worker.start();
}

DiagWaitDBOperation::~DiagWaitDBOperation()
{
    delete ui;
}
