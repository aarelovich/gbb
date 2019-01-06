#ifndef DIAGCSVIMPORT_H
#define DIAGCSVIMPORT_H

#include <QDialog>
#include <QMessageBox>
#include <QTableWidget>

#include "csvimporter.h"

namespace Ui {
class DiagCSVImport;
}

class DiagCSVImport : public QDialog
{
    Q_OBJECT

public:
    explicit DiagCSVImport(QWidget *parent = 0);

    // Returning a pointer for the CSV importer in order to set it up.
    CSVImporter * getCSVImporter() {return &csvImporter;}

    ~DiagCSVImport();

protected:
    void showEvent(QShowEvent *e);

private slots:

    void on_csvThreadDone();

    void on_pbAplicarCambios_clicked();

    void on_pbCancelar_clicked();

private:
    Ui::DiagCSVImport *ui;
    CSVImporter csvImporter;

    void fillWidgetTables(QTableWidget *tw, const QList<ProductInfo> &list);

};

#endif // DIAGCSVIMPORT_H
