#include "gbbmain.h"
#include "ui_gbbmain.h"

GBBMain::GBBMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GBBMain)
{
    ui->setupUi(this);

    this->setWindowTitle("GBB Stock - " + QString(APP_VERSION));

    // Setting up de the DB and testing the connection.
    db.setupDB("",DB_HOST,DB_NAME,DB_USER,DB_PASSWD,DB_PORT);
    if (!db.open()){
        errorLog("No se puede inicializar la conexión a la base de datos: " + db.getError());
        showError("Error crítico de base de datos. El programa no podrá utilizarze\nContactarse con Ariel Arelovich: aarelovich@gmail.com");
        // TODO inhabilitar operaciones con base de datos.
        return;
    }

    // Testing was successfull.
    db.close();



}


//----------------------- AUX FUNCTIONS
void GBBMain::showError(const QString &error){
    QMessageBox::critical(this,"Ha ocurrido un error",error,QMessageBox::Ok);
}


GBBMain::~GBBMain()
{
    delete ui;
}



//----------------------- MENU FUNCTIONS
void GBBMain::on_actionAgregar_un_nuevo_producto_triggered()
{
    DialogProduct diag(this);
    diag.exec();
}
