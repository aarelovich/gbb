#ifndef DIAGWAITDBRESTORE_H
#define DIAGWAITDBRESTORE_H

#include <QDialog>
#include <QTimer>
#include "dbworkerthread.h"

namespace Ui {
class DiagWaitDBRestore;
}

class DiagWaitDBRestore : public QDialog
{
    Q_OBJECT

public:
    explicit DiagWaitDBRestore(QWidget *parent = 0);
    DBWorkerThread * getWorkerThread() { return &worker; }
    ~DiagWaitDBRestore();

private:
    void showEvent(QShowEvent *e);

private:
    Ui::DiagWaitDBRestore *ui;
    DBWorkerThread worker;
};

#endif // DIAGWAITDBRESTORE_H
