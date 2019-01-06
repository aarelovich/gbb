#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QHash>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QCryptographicHash>

#include "global.h"

class DBInterface
{
public:

    DBInterface();

    // Initializes the connection to thez database returning true if sucessfull.
    bool openConnection(const QString &instanceName, const QString &host, const QString &dbname, const QString &user, const QString &passwd, quint16 port);

    // Insert Query
    bool insertDB(const QString &table, const QStringList &columns, const QStringList &values, QSet<QString> skipParenthesisCheck = QSet<QString>());

    // Select Query. Returns the first row only
    bool readFromDB(const QString &table, const QStringList &columns, const QString &conditions, bool distinct = false);

    // Update Query.
    bool updateDB(const QString &table, const QStringList &columns, const QStringList &values, const QString &condition);

    // Delete Query
    bool deleteRowFromDB(const QString &table, const QString &condition);

    // Get last generated keyid from a table;
    qint32 getNewestKeyid(const QString &keyidColName, const QString &table);

    // The advanced search function.
    bool searchDB(const QString &tableName, const QString &searchStr, const QStringList &columnsToSearch, const QStringList &keyidSubset,
                  const QStringList &colsToReturn, const QString &keyidColumn = "keyid");

    bool createDBBKP(const QString &file);
    bool restoreBKP(const QString &filename);

    // Closing the connection.
    void close() { dbConnection.close(); }

    QString getError() const {return error;}
    DBData getLastResult() const {return lastResult;}

private:

    // The connectiont tot he database
    QSqlDatabase dbConnection;

    // The last error produces
    QString error;

    // The last result (a single row).
    DBData lastResult;

    // Making sure init is only called once.
    bool dbSetupDone;

    // Used for backup
    bool bkpTable(const QString &table, QTextStream *writer);

};

#endif // DBINTERFACE_H
