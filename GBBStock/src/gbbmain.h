#ifndef GBBMAIN_H
#define GBBMAIN_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QSettings>
#include <QDir>
#include <QDateTime>
#include <QCoreApplication>

#include "dialogproduct.h"
#include "diagadvsearch.h"
#include "dbinterface.h"
#include "diagcsvimport.h"
#include "diagdbbkp.h"
#include "diagminstockselect.h"
#include "diagchangeinmultiplefields.h"
#include "diagventa.h"
#include "diagsalehistory.h"


namespace Ui {
class GBBMain;
}

class GBBMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit GBBMain(QWidget *parent = 0);
    ~GBBMain();

private slots:
    void on_actionAgregar_un_nuevo_producto_triggered();

    void on_pbAdvSearch_clicked();

    void on_actionImportar_planilla_CSV_triggered();

    void on_pbSearch_clicked();

    void on_pbCleanSearch_clicked();

    void on_pbVenta_clicked();

    void on_actionRealizar_Backup_triggered();

    void onCellChanged(int row, int col, int prow, int pcol);
    void onCellDoubleClicked(int row, int col);

    void on_actionProductos_por_debajo_del_stock_minimo_triggered();

    void on_pbModFormulaCostos_clicked();

    void on_pbMassChange_clicked();

    void on_pbHistVentas_clicked();

private:
    Ui::GBBMain *ui;
    DBInterface db;

    // To open in the same place everytime something is searched.
    QStringList searchColumns;
    QStringList searchKeys;
    QStringList displayKeys;

    // Map for equivalent column names to title names for the stock table.
    QMap<QString,QString> colNameToTitleName;

    // Where the search results are stored.
    QList<ProductInfo> searchResults;

    // Auxiliary functions.
    void showError(const QString &error);
    void fillResultsTable(const DBData &sres);

    // Calculate dashboard values;
    void updateDashboard();

};

#endif // GBBMAIN_H
