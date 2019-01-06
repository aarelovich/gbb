#ifndef DIAGMINSTOCKSELECT_H
#define DIAGMINSTOCKSELECT_H

#include <QDialog>
#include "dbinterface.h"

namespace Ui {
class DiagMinStockSelect;
}

class DiagMinStockSelect : public QDialog
{
    Q_OBJECT

public:
    explicit DiagMinStockSelect(QWidget *parent = 0);
    ~DiagMinStockSelect();
    QString getCondition() const {return condition;}
private slots:
    void on_pbOk_clicked();
    void on_pbCancel_clicked();
private:
    Ui::DiagMinStockSelect *ui;
    QString condition;
};

#endif // DIAGMINSTOCKSELECT_H
