#ifndef DIAGDBBKP_H
#define DIAGDBBKP_H

#include <QDialog>
#include <QDir>
#include <QMessageBox>

#include "dbinterface.h"
#include "global.h"
#include "diagwaitdboperation.h"

namespace Ui {
class DiagDBBkp;
}

class DiagDBBkp : public QDialog
{
    Q_OBJECT

public:
    explicit DiagDBBkp(QWidget *parent = 0);

    void setDBInterface(DBInterface *dbi){db = dbi;}

    ~DiagDBBkp();

private slots:
    void on_pbCreate_clicked();

    void on_pbRestore_clicked();

    void on_pbDelete_clicked();

    void on_pushButton_4_clicked();

protected:
    void showEvent(QShowEvent *e);

private:
    Ui::DiagDBBkp *ui;

    DBInterface *db;

    void refreshBkpList();

};

#endif // DIAGDBBKP_H
