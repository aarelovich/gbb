#ifndef DBRESTORE_H
#define DBRESTORE_H

#include <QThread>
#include "calculator.h"
#include "dbinterface.h"

class DBWorkerThread : public QThread
{
    Q_OBJECT
public:
    DBWorkerThread();

    typedef enum {DBO_RESTORE_DB,DBO_APPLY_FORMULAS} DBOperation;

    void setDBInterface(DBInterface *dbi) {db = dbi;}

    // Setting the operation to do.
    void setRestoreDBFile(const QString &file) {dbo = DBO_RESTORE_DB; restoreFile = file;}
    void setDBApplyFormulas(const QStringList &kidSubset) {dbo = DBO_APPLY_FORMULAS; keyidSubset = kidSubset;}

    void run();

    bool getResult() const {return result;}
    QSet<QString> getBadSyntax() const {return wrongSyntax;}

private:
    bool result;
    DBOperation dbo;
    QString restoreFile;
    QString syntaxError;
    DBInterface *db;
    QSet<QString> wrongSyntax;
    QStringList keyidSubset;

    void applyFormulas(bool isPublic);

};

#endif // DBRESTORE_H
