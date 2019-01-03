#include "gbbmain.h"
#include "ui_gbbmain.h"

GBBMain::GBBMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GBBMain)
{
    ui->setupUi(this);
}

GBBMain::~GBBMain()
{
    delete ui;
}
