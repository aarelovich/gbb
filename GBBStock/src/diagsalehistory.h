#ifndef DIAGSALEHISTORY_H
#define DIAGSALEHISTORY_H

#include <QDialog>
#include <QDateTime>
#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices>

#include "dbinterface.h"

namespace Ui {
class DiagSaleHistory;
}

class DiagSaleHistory : public QDialog
{
    Q_OBJECT

public:
    explicit DiagSaleHistory(QWidget *parent = 0);
    void setDBInterface(DBInterface *dbi) {db = dbi;}
    ~DiagSaleHistory();

private slots:
    void on_leSearch_returnPressed();
    void on_pbButton_clicked();
    void openPDF(int row, int col);
    void showNote(int row, int col);

protected:
    void showEvent(QShowEvent *e);

private:
    Ui::DiagSaleHistory *ui;
    DBInterface *db;
    QMap<QString,ProductInfo> productSearchResults;
    QList<ProductInfo> salesSearchResult;

    QString dbDateToShowDate(const QString &dbdate);

};

#endif // DIAGSALEHISTORY_H
