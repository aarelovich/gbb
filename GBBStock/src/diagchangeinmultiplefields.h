#ifndef DIAGCHANGEINMULTIPLEFIELDS_H
#define DIAGCHANGEINMULTIPLEFIELDS_H

#include <QDialog>
#include <QStringList>
#include <QMessageBox>

#include "calculator.h"
#include "global.h"

namespace Ui {
class DiagChangeInMultipleFields;
}

class DiagChangeInMultipleFields : public QDialog
{
    Q_OBJECT

public:
    explicit DiagChangeInMultipleFields(QWidget *parent = 0);
    ~DiagChangeInMultipleFields();
    void setColumnsAndNames(const QMap<QString,QString> colsAndFields);
    QString getFormula() const;
    QString getValue() const;
    QString getTableColumn() const;

private slots:
    void on_cbCampo_currentIndexChanged(int index);

    void on_cbModType_currentIndexChanged(int index);

    void on_pbOk_clicked();

    void on_pbCancel_clicked();

protected:
    void showEvent(QShowEvent *e);

private:
    Ui::DiagChangeInMultipleFields *ui;
    QSet<QString> fieldsWithIntValidator;
    QSet<QString> fieldsWithDoubleValidator;
};

#endif // DIAGCHANGEINMULTIPLEFIELDS_H
