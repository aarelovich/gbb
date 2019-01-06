#ifndef DIAGWAITDBRESTORE_H
#define DIAGWAITDBRESTORE_H

#include <QDialog>
#include "dbworkerthread.h"

namespace Ui {
class DiagWaitDBRestore;
}

class DiagWaitDBOperation : public QDialog
{
    Q_OBJECT

public:
    explicit DiagWaitDBOperation(QWidget *parent = 0);
    DBWorkerThread * getWorkerThread() { return &worker; }
    ~DiagWaitDBOperation();

private:
    void showEvent(QShowEvent *e);

private:
    Ui::DiagWaitDBRestore *ui;
    DBWorkerThread worker;
};

#endif // DIAGWAITDBRESTORE_H
