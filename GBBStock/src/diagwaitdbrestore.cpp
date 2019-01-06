#include "diagwaitdbrestore.h"
#include "ui_diagwaitdbrestore.h"

DiagWaitDBRestore::DiagWaitDBRestore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagWaitDBRestore)
{
    ui->setupUi(this);
    connect(&worker,SIGNAL(finished()),this,SLOT(accept()));
}

void DiagWaitDBRestore::showEvent(QShowEvent *e){
    QDialog::showEvent(e);
    worker.start();
}

DiagWaitDBRestore::~DiagWaitDBRestore()
{
    delete ui;
}
