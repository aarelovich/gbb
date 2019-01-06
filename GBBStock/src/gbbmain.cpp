#include "gbbmain.h"
#include "ui_gbbmain.h"

GBBMain::GBBMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GBBMain)
{
    ui->setupUi(this);

    this->setWindowTitle("GBB Stock - " + QString(APP_VERSION));

    // Setting up de the DB and testing the connection.

    if (!db.openConnection("",DB_HOST,DB_NAME,DB_USER,DB_PASSWD,DB_PORT)){
        errorLog("No se puede inicializar la conexión a la base de datos: " + db.getError());
        showError("Error crítico de base de datos. El programa no podrá utilizarze\nContactarse con Ariel Arelovich: aarelovich@gmail.com");
        // TODO inhabilitar operaciones con base de datos.
        return;
    }


    searchColumns      << TSTOCK_COL_PRODUCTO << TSTOCK_COL_NOMBRE_ALT << TSTOCK_COL_DESC << TSTOCK_COL_LOCAT
                       << TSTOCK_COL_COL << TSTOCK_COL_ESTANTE << TSTOCK_COL_TIPO_PROD << TSTOCK_COL_ENV
                       << TSTOCK_COL_MARCA << TSTOCK_COL_FORMULA_M << TSTOCK_COL_FORMULA_P;

    displayKeys        << TSTOCK_COL_COSTP << TSTOCK_COL_COSTM << TSTOCK_COL_STOCK_F << TSTOCK_COL_STOCK_D
                       << TSTOCK_COL_NOMBRE_ALT << TSTOCK_COL_DESC << TSTOCK_COL_LOCAT << TSTOCK_COL_COL << TSTOCK_COL_ESTANTE
                       << TSTOCK_COL_STOCK_MIN_F << TSTOCK_COL_STOCK_MIN_D;

    colNameToTitleName[TSTOCK_COL_KEYID] = "";
    colNameToTitleName[TSTOCK_COL_PRODUCTO] = "Producto";
    colNameToTitleName[TSTOCK_COL_NOMBRE_ALT] = "Nombre Alternativo";
    colNameToTitleName[TSTOCK_COL_DESC] = "Descripción";
    colNameToTitleName[TSTOCK_COL_COST] = "Costo";
    colNameToTitleName[TSTOCK_COL_COSTP] = "Costo Público";
    colNameToTitleName[TSTOCK_COL_COSTM] = "Costo Mayorista";
    colNameToTitleName[TSTOCK_COL_STOCK_D] = "Stock (Depósito)";
    colNameToTitleName[TSTOCK_COL_STOCK_F] = "Stock (Frente)";
    colNameToTitleName[TSTOCK_COL_LOCAT] = "Ubicación";
    colNameToTitleName[TSTOCK_COL_COL] = "Columna";
    colNameToTitleName[TSTOCK_COL_ESTANTE] = "Estante";
    colNameToTitleName[TSTOCK_COL_MARCA] = "Marca";
    colNameToTitleName[TSTOCK_COL_TIPO_PROD] = "Tipo de Producto";
    colNameToTitleName[TSTOCK_COL_ENV] = "Envase";
    colNameToTitleName[TSTOCK_COL_STOCK_MIN_D] = "Stock Mínimo (Depósito)";
    colNameToTitleName[TSTOCK_COL_STOCK_MIN_F] = "Stock Mínimo (Frente))";
    colNameToTitleName[TSTOCK_COL_FORMULA_M] = "Formula Precio Mayorista";
    colNameToTitleName[TSTOCK_COL_FORMULA_P] = "Formula Precio Público";

    ui->twSearchResults->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->leSearch,SIGNAL(returnPressed()),this,SLOT(on_pbSearch_clicked()));

    connect(ui->twSearchResults,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(onCellChanged(int,int,int,int)));
    connect(ui->twSearchResults,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(onCellDoubleClicked(int,int)));

}


//----------------------- AUX FUNCTIONS
void GBBMain::showError(const QString &error){
    QMessageBox::critical(this,"Ha ocurrido un error",error,QMessageBox::Ok);
}

void GBBMain::fillResultsTable(const DBData &sres){
    QStringList dataColumns = colNameToTitleName.keys();
    searchResults.clear();
    for (qint32 i = 0; i < sres.rows.size(); i++){
        ProductInfo info;
        //qWarning() << "=========== ROW has size of " << sres.rows.at(i).size();
        for (qint32 j = 0; j < sres.rows.at(i).size(); j++){
            //qWarning() << "Adding column" << dataColumns.at(j) << "the value" << sres.rows.at(i).at(j);
            info[dataColumns.at(j)] = sres.rows.at(i).at(j);
        }
        searchResults << info;
    }

    // Showing the table.
    ui->twSearchResults->blockSignals(true);
    ui->twSearchResults->clear();

    QStringList headerCols; headerCols << TSTOCK_COL_PRODUCTO << TSTOCK_COL_MARCA << TSTOCK_COL_TIPO_PROD << TSTOCK_COL_ENV;
    QStringList headerNames;

    for (qint32 i = 0; i < headerCols.size(); i++){
        headerNames << colNameToTitleName.value(headerCols.at(i));
    }

    ui->twSearchResults->setRowCount(searchResults.size());
    ui->twSearchResults->setColumnCount(headerCols.size());
    ui->twSearchResults->setHorizontalHeaderLabels(headerNames);

    searchKeys.clear();
    for (qint32 i = 0; i < searchResults.size(); i++){
        // Adding the keyid to the new subsett
        searchKeys << searchResults.at(i).value(TSTOCK_COL_KEYID);
        for (qint32 j = 0; j < headerCols.size(); j++){
            QTableWidgetItem *item = new QTableWidgetItem(searchResults.at(i).value(headerCols.at(j)));
            ui->twSearchResults->setItem(i,j,item);
            item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
            item->setData(DATA_ROLE_SEARCH_INDEX,i);
        }
    }

    ui->twSearchResults->blockSignals(false);
}

//----------------------- BUTTON FUNCTIONS
void GBBMain::on_pbAdvSearch_clicked()
{    
    DiagAdvSearch diag(this);
    diag.setActiveColumns(searchColumns);
    if (diag.exec() == QDialog::Accepted){
        searchColumns = diag.getActiveColumns();
    }

}

void GBBMain::on_pbCleanSearch_clicked()
{
    ui->leSearch->clear();
    ui->twSearchResults->clear();
    ui->twSearchResults->setRowCount(0);
    ui->twSearchResults->setColumnCount(0);
    ui->pteExtendedInfo->clear();
    searchResults.clear();
    searchKeys.clear();
}

void GBBMain::on_pbSearch_clicked()
{

    QString searchString = ui->leSearch->text();
    if (searchString.isEmpty()) return;
    QStringList dataColumns = colNameToTitleName.keys();
    //qWarning() << dataColumns;
    if (!db.searchDB(TABLE_STOCK,searchString,searchColumns,searchKeys,dataColumns)){
        errorLog("Searching the DB, an error: " + db.getError());
        showError("Hubo un problema con la base de datos al realizar la búsqueda\nIntente nuevamente con otra palabra");
        return;
    }

    fillResultsTable(db.getLastResult());

}

void GBBMain::on_pbModFormulaCostos_clicked()
{
    QString what;
    if (searchKeys.isEmpty()) what = "todos los productos";
    else what = " los productos en pantalla ";

    int ans = QMessageBox::question(this,"Confirmar acción",
                          "Esto actualizará los precios público y mayoristas de " + what + " aque tengan la fórmula de cálculo ingresada.\nConfirme que desea continuar?",
                          QMessageBox::Ok,QMessageBox::Cancel);
    if (ans == QMessageBox::Cancel) return;
    DiagWaitDBRestore diag(this);
    diag.getWorkerThread()->setDBInterface(&db);
    diag.getWorkerThread()->setDBApplyFormulas(searchKeys);
    diag.exec();

    if (!diag.getWorkerThread()->getResult()){
        showError("Hubo errores al intentar actualizar los precios con la base de datos");
        return;
    }

    QStringList badSyntax = diag.getWorkerThread()->getBadSyntax().toList();
    if (!badSyntax.isEmpty()){
        QString message;
        for (qint32 i = 0; i < badSyntax.size(); i++){
            message = message + badSyntax.at(i) + "\n";
        }
        message = "Las siguientes fórmulas tienen errores de syntasis. Los valores de precios no fueron actualizados en estos casos:\n" + message;
        showError(message);
    }
}


void GBBMain::on_pbVenta_clicked()
{

//    QString filename = "C:/Users/Viewmind/Documents/QtProjects/Doc/overview.pdf";
//    QUrl uri = QUrl::fromLocalFile(filename);
//    QDesktopServices::openUrl(uri);

}


//----------------------- MENU FUNCTIONS
void GBBMain::on_actionAgregar_un_nuevo_producto_triggered()
{
    DialogProduct diag(this);
    diag.setProductInformation(ProductInfo(),&db);
    diag.exec();
    on_pbCleanSearch_clicked();
}

void GBBMain::on_actionRealizar_Backup_triggered()
{
    DiagDBBkp diag(this);
    diag.setDBInterface(&db);
    diag.exec();
}

void GBBMain::on_actionImportar_planilla_CSV_triggered()
{
    QSettings settings(SETTINGS_SETTINGS);
    QString path = settings.value(SETTINGS_SEARCH_DIR,".").toString();

    QString filename = QFileDialog::getOpenFileName(this,"CSV a importar",path,"CSV (*.csv)");
    //filename = "C:/Users/Viewmind/Documents/GBB/MYSQLDB/XLSStock/stock_gulf - Sheet1.csv";
    if (filename.isEmpty()) return;

    QFileInfo info(filename);
    settings.setValue(SETTINGS_SEARCH_DIR,info.absoluteDir().absolutePath());

    DiagCSVImport diag(this);

    diag.getCSVImporter()->setCSVFilePath(filename);
    diag.getCSVImporter()->setDatabaseConnection(&db);

    diag.exec();

}

void GBBMain::on_actionProductos_por_debajo_del_stock_minimo_triggered()
{
    on_pbCleanSearch_clicked();

    DiagMinStockSelect diag(this);
    if (diag.exec() == QDialog::Rejected) return;
    QString condition = diag.getCondition();

    QStringList dataColumns = colNameToTitleName.keys();
    //qWarning() << dataColumns;
    if (!db.readFromDB(TABLE_STOCK,dataColumns,condition)){
        errorLog("Searching the DB, an error: " + db.getError());
        showError("Hubo un problema con la base de datos al realizar la búsqueda\nIntente nuevamente con otra palabra");
        return;
    }

    fillResultsTable(db.getLastResult());
}

void GBBMain::on_pbMassChange_clicked()
{

}

//----------------------- OTHER SLOTS
void GBBMain::onCellChanged(int row, int col, int prow, int pcol){
    Q_UNUSED(col)
    Q_UNUSED(pcol)
    Q_UNUSED(prow)
    ProductInfo info = searchResults.at(row);
    QString html;
    for (qint32 i = 0; i < displayKeys.size(); i++){
        html = html + "<p><span style='font-family=Mono; font-size:10pt; font-weight:600'><b>" + colNameToTitleName.value(displayKeys.at(i)) + ": </b></span>";
        html = html + "<span style='font-family=Mono; font-size:10pt; font-weight:400'>" + info.value(displayKeys.at(i)) + "</span></p>";
    }
    ui->pteExtendedInfo->setHtml(html);
}

void GBBMain::onCellDoubleClicked(int row, int col){
    Q_UNUSED(col);
    DialogProduct diag(this);
    diag.setProductInformation(searchResults.at(row),&db);
    diag.exec();
}

GBBMain::~GBBMain()
{
    db.close();
    delete ui;
}



