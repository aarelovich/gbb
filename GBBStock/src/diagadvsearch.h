#ifndef DIAGADVSEARCH_H
#define DIAGADVSEARCH_H

#include <QDialog>
#include "global.h"

namespace Ui {
class diagadvsearch;
}

class DiagAdvSearch : public QDialog
{
    Q_OBJECT

public:
    explicit DiagAdvSearch(QWidget *parent = 0);

    void setActiveColumns(const QStringList &searchCols);
    QStringList getActiveColumns();

    ~DiagAdvSearch();

private slots:
    void on_pbSellAll_clicked();

    void on_pbSellNone_clicked();

private:
    Ui::diagadvsearch *ui;
};

#endif // DIAGADVSEARCH_H
