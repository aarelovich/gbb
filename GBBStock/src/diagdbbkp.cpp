#include "diagdbbkp.h"
#include "ui_diagdbbkp.h"

DiagDBBkp::DiagDBBkp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagDBBkp)
{
    ui->setupUi(this);
}

DiagDBBkp::~DiagDBBkp()
{
    delete ui;
}

void DiagDBBkp::on_pbCreate_clicked()
{
    QDir currentDir(".");
    currentDir.mkdir(DIR_BKP);
    QString date = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm");
    QString bkpFile = "./" + QString(DIR_BKP) +  "/" + date + ".gbbdd";
    if (!db->createDBBKP(bkpFile)){
        QMessageBox::critical(this,"Creación de respaldo","No fue posible realizar la copia de respaldo de la base de datos",QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this,"Copia de respaldo creada","Se ha creado con éxito la copia de seguridad.",QMessageBox::Ok);
    }
    refreshBkpList();
}

void DiagDBBkp::on_pbRestore_clicked()
{
    if (ui->lwBackups->currentRow() < 0) return;
    QString restorfile = ui->lwBackups->currentItem()->data(DATA_ROLE_BKP_FNAME).toString();
    restorfile = QString(DIR_BKP) + "/" + restorfile;
    int ans = QMessageBox::question(this,"Restaurar de copia de respaldo","Está apunto de restaurar una base de datos vieja\nLos cambios hechos a partir de la fecha del respaldo se perderán.\nPresione OK para proceder",
                          QMessageBox::Ok,QMessageBox::Cancel);
    if (ans == QMessageBox::Cancel) return;

    DiagWaitDBOperation diag(this);
    diag.getWorkerThread()->setDBInterface(db);
    diag.getWorkerThread()->setRestoreDBFile(restorfile);
    diag.exec();

    if (!diag.getWorkerThread()->getResult()){
        errorLog("Restoring DB: " + db->getError());
        QMessageBox::critical(this,"Restauracion del respaldo","No fue posible realizar la restauración. Es posible que los datos se hayan perdido.\nContactar a Ariel Arelovich",QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this,"Restauración finalizada","Se ha restaurado la copia de seguridad con éxito",QMessageBox::Ok);
    }
}

void DiagDBBkp::showEvent(QShowEvent *e){
    QDialog::showEvent(e);
    refreshBkpList();
}

void DiagDBBkp::on_pbDelete_clicked()
{
    if (ui->lwBackups->currentRow() < 0) return;
    QString restorfile = ui->lwBackups->currentItem()->data(DATA_ROLE_BKP_FNAME).toString();
    restorfile = QString(DIR_BKP) + "/" + restorfile;
    int ans = QMessageBox::question(this,"Confirmación","Confirma que desea eliminar la copia de seguridad: " + ui->lwBackups->currentItem()->text(),
                          QMessageBox::Ok,QMessageBox::Cancel);
    if (ans == QMessageBox::Cancel) return;

    QFile file(restorfile);
    file.remove();
    refreshBkpList();
}

void DiagDBBkp::refreshBkpList(){

    ui->lwBackups->clear();
    QDir dir(DIR_BKP);
    if (!dir.exists()) return;
    QStringList filters; filters << "*.gbbdd";
    QStringList files = dir.entryList(filters,QDir::Files,QDir::Name);
    for (qint32 i = 0; i < files.size(); i++){
        QStringList parts = files.at(i).split(".");
        QString name = parts.first();
        parts = name.split("_");
        if (parts.size() == 5)
           name = parts[2] + "/" + parts[1] + "/" + parts[0] + " " + parts[3] + ":" + parts[4];
        QListWidgetItem *item = new QListWidgetItem(name,ui->lwBackups);
        item->setData(DATA_ROLE_BKP_FNAME,files.at(i));
    }
}

void DiagDBBkp::on_pushButton_4_clicked()
{
    this->accept();
}
