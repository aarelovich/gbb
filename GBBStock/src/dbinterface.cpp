#include "dbinterface.h"

DBInterface::DBInterface()
{
    dbSetupDone = false;
}

bool DBInterface::openConnection(const QString &instanceName, const QString &host, const QString &dbname, const QString &user, const QString &passwd, quint16 port){

    if (dbSetupDone) {
        error = "Attempting to open an allready opened connection";
        return false;
    }

    dbConnection = QSqlDatabase::addDatabase("QMYSQL",instanceName);
    dbConnection.setHostName(host);
    dbConnection.setDatabaseName(dbname);
    dbConnection.setUserName(user);
    dbConnection.setPassword(passwd);
    //qWarning() << "Setting up DB Connection" << instanceName << "with " << dbConnection.userName() << dbConnection.password();
    if (port != 0){
        dbConnection.setPort(port);
    }

    if (!dbConnection.open()){
        error = dbConnection.lastError().text();
        return false;
    }

    dbSetupDone = true;

    return true;
}

bool DBInterface::insertDB(const QString &table, const QStringList &columns, const QStringList &values, QSet<QString> skipParenthesisCheck){

    if (!dbSetupDone) return false;

    QString query = "INSERT INTO " + table + "(";

    QStringList quotedVals;
    for (qint32 i = 0; i < values.size(); i++){
        if (!values.at(i).contains('(')){
            quotedVals << "'" + values.at(i) + "'";
        }
        else{
            if (skipParenthesisCheck.contains(columns.at(i))) quotedVals << "'" + values.at(i) + "'";
            else quotedVals << values.at(i);
        }
    }

    query = query  + columns.join(",") + ") VALUES (" + quotedVals.join(",") + ")";

    QSqlQuery q(dbConnection);

    //qWarning() << "INSERT QUERY" << query;

    if (!q.exec(query)){
        error = "INSERT Error on query: " + query + ". ERROR: " + q.lastError().text();
        return false;
    }

    return true;

}

bool DBInterface::searchDB(const QString &tableName,
                           const QString &searchStr, const QStringList &columnsToSearch, const QStringList &keyidSubset,
                           const QStringList &colsToReturn ,const QString &keyidColumn){

    if (!dbSetupDone) return false;
    QString query = "SELECT ";
    query = query + colsToReturn.join(",");

    query = query + " FROM " + tableName + " WHERE ";

    QStringList conditionList;
    for (qint32 i = 0; i < columnsToSearch.size(); i++){
        conditionList << "( " + columnsToSearch.at(i) + " LIKE '%" + searchStr + "%')";
    }

    query = query  + "("  + conditionList.join(" OR ") + ")";

    if (!keyidSubset.isEmpty()){
        query = query + " AND " + keyidColumn + " IN ('" + keyidSubset.join("', '") + "')";
    }

    QSqlQuery q(dbConnection);

    //qWarning() << "SEARCH QUERY: " << query;

    if (!q.exec(query)){
        error = "SEARCH query error: " + query + ". ERROR: " + q.lastError().text();
        return false;
    }

    lastResult.clear();

    lastResult.columns = colsToReturn;

    while (q.next()){
        QStringList row;
        for (qint32 i = 0; i < colsToReturn.size(); i++){
            row << q.value(i).toString();
        }
        lastResult.rows << row;
    }


    return true;

}

bool DBInterface::updateDB(const QString &table, const QStringList &columns, const QStringList &values, const QString &condition){

    if (!dbSetupDone) return false;

    QString query = "UPDATE ";
    if (columns.isEmpty()){
        error = "SELECT Error. Columns cannot be an empty list";
        return false;
    }

    query = query + table + " SET ";
    QStringList tojoin;
    for (qint32 i = 0; i < columns.size(); i++){
        tojoin << columns.at(i) + " = '" + values.at(i) + "'";
    }
    query = query + tojoin.join(",");
    if (condition.isEmpty()){
        error = "UPDATE Error: Cannto update withouth a condition";
        return false;
    }
    query = query + " WHERE " + condition;

    QSqlQuery q(dbConnection);
    if (!q.exec(query)){
        error = "UPDATE Error on query: " + query + ". ERROR: " + q.lastError().text();
        return false;
    }

    return true;

}

bool DBInterface::deleteRowFromDB(const QString &table, const QString &condition){

    if (!dbSetupDone) return false;

    QString query = "DELETE FROM " + table + " WHERE " + condition;
    QSqlQuery q(dbConnection);
    if (!q.exec(query)){
        error = "DELETE Error on query: " + query + ". ERROR: " + q.lastError().text();
        return false;
    }

    return true;
}

qint32 DBInterface::getNewestKeyid(const QString &keyidColName, const QString &table){

    if (!dbSetupDone) return false;

    QString query = "SELECT MAX(" + keyidColName + ") FROM " + table;
    QSqlQuery q(dbConnection);
    if (!q.exec(query)){
        error = "SELECT MAX, Error on query: " + query + ". ERROR: " + q.lastError().text();
        return -1;
    }

    if (!q.next()){
        error = "SELECT MAX Did not rerturn any results";
        return -1;
    }

    return q.value(0).toInt();

}

bool DBInterface::readFromDB(const QString &table, const QStringList &columns, const QString &conditions, bool distinct){

    if (!dbSetupDone) return false;

    QString query = "SELECT ";
    if (distinct) query = query + " DISTINCT ";
    if (columns.isEmpty()){
        error = "SELECT Error. Columns cannot be an empty list";
        return false;
    }
    query = query + columns.join(",");
    query = query + " FROM " + table;
    if (conditions != ""){
        query = query + " WHERE " + conditions;
    }

    QSqlQuery q(dbConnection);
    //qWarning() << "EXECUTING READ QUERY: " << query;
    if (!q.exec(query)){
        error = "SELECT Error on query: " + query + ". ERROR: " + q.lastError().text();
        return false;
    }

    lastResult.clear();

    lastResult.columns = columns;

    while (q.next()){
        QStringList row;
        for (qint32 i = 0; i < columns.size(); i++){
            row << q.value(i).toString();
        }
        lastResult.rows << row;
    }
    return true;
}


bool DBInterface::createDBBKP(const QString &file){

    if (!dbSetupDone) return false;

    // Getting all tables.
    QSqlQuery q(dbConnection);
    QString query = "SHOW TABLES";
    if (!q.exec(query)){
        error = "Show tables query: " + query + ". ERROR: " + q.lastError().text();
        return false;
    }

    QStringList tables;
    while (q.next()){
        tables << q.value(0).toString();
    }

    QFile filetowrite(file);
    if (!filetowrite.open(QFile::WriteOnly)) {
        error = "Could not open write file: " + file;
        return false;
    }

    QTextStream writer(&filetowrite);
    writer.setCodec("UTF-8");

    for (qint32 i = 0; i < tables.size(); i++){
        if (!bkpTable(tables.at(i),&writer)){
            filetowrite.close();
            return false;
        }
    }

    filetowrite.close();

    return true;
}

bool DBInterface::restoreBKP(const QString &filename){

    if (!dbSetupDone) return false;

    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        error = "Could not open read file: " + filename;
        return false;
    }

    QTextStream reader(&file);
    reader.setCodec("UTF-8");

    QSqlQuery q(dbConnection);

    while (!reader.atEnd()){
        QString query = reader.readLine();
        if (!q.exec(query)){
            error = "Restore BKP Query: " + query + ". ERROR: " + q.lastError().text();
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

bool DBInterface::bkpTable(const QString &table, QTextStream *writer){

    *writer << "DELETE FROM " + table << ";\n";

    QSqlQuery q(dbConnection);
    QString query = "DESCRIBE " + table;
    if (!q.exec(query)){
        error = "Describe table " + table + ": " + query + ". ERROR: " + q.lastError().text();
        return false;
    }

    QStringList columnNames;
    while (q.next()){
        // First column should be the column name
        columnNames << q.value(0).toString();
    }

    query = "SELECT " + columnNames.join(",") + " FROM " + table;
    if (!q.exec(query)){
        error = "Selecting all columns from table " + table + ": " + query + ". ERROR: " + q.lastError().text();
        return false;
    }

    while (q.next()){
        QStringList quotedVals;
        for (qint32 i = 0; i < columnNames.size(); i++){
            quotedVals << "'" + q.value(i).toString() + "'";
        }
        *writer << "INSERT INTO " + table + "(" + columnNames.join(",") + ") VALUES ("  + quotedVals.join(",") + ");\n";
    }

    return true;

}
