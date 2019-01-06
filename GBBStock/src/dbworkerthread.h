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

    typedef enum {DBO_RESTORE_DB,DBO_APPLY_FORMULAS,DBO_MOD_FIELD_WITH_FORMULA,DBO_MOD_FIELD_VALUE} DBOperation;

    void setDBInterface(DBInterface *dbi) {db = dbi;}

    // Setting the operation to do.
    void setRestoreDBFile(const QString &file) {dbo = DBO_RESTORE_DB; restoreFile = file;}
    void setDBApplyFormulas(const QStringList &kidSubset) {dbo = DBO_APPLY_FORMULAS; keyidSubset = kidSubset;}
    void setDBApplyFormulaToField(const QString &formula, const QString &field, const QStringList &kidSubset){ dbo = DBO_MOD_FIELD_WITH_FORMULA;
                                                                                                               fieldValue = formula;
                                                                                                               keyidSubset = kidSubset;
                                                                                                               operationColumn = field;}
    void setDBFillFieldsWithValue(const QString &value, const QString &field, const QStringList &kidSubset){ dbo = DBO_MOD_FIELD_VALUE;
                                                                                                             fieldValue = value;
                                                                                                             keyidSubset = kidSubset;
                                                                                                             operationColumn = field;}
    void run();

    bool getResult() const {return result;}
    QSet<QString> getBadSyntax() const {return wrongSyntax;}

private:

    // The db interface, the operation type and the result
    bool result;
    DBOperation dbo;
    DBInterface *db;

    // Variables required for each of the operations.
    QString restoreFile;
    QString syntaxError;    
    QString fieldValue;
    QString operationColumn;
    QSet<QString> wrongSyntax;
    QStringList keyidSubset;

    // The operation functions.
    void applyCostFormulas(bool isPublic);
    void applyFormulaToField();
    void modFieldWithValue();


};

#endif // DBRESTORE_H
