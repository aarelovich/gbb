#ifndef CSVIMPORTER_H
#define CSVIMPORTER_H

#include <QThread>
#include <iostream>

#include "dbinterface.h"
#include "csvreader.h"

class CSVImporter: public QThread
{
    Q_OBJECT
public:

    CSVImporter();

    // Configuring the import
    void setDatabaseConnection(DBInterface *dbi) {db = dbi;}
    void setCSVFilePath(const QString &filename) {csvFile = filename;}
    void setPrepareMode(bool pmode) {prepareMode = pmode;}
    bool getPrepareMode() const {return prepareMode;}

    // Getting the results
    QList<ProductInfo> getProductList(bool lookForUpdates) const;

    void run();
    QString getError() const {return error;}

signals:
    void updateProgress(qint32 prog);

private:

    struct TableUpdateStruct {
        QString condition;
        QStringList columns;
        QStringList values;
    };

    typedef QList<TableUpdateStruct> TableUpdateList;

    TableUpdateList tUpdates;

    QString error;
    QString csvFile;
    DBInterface *db;
    bool prepareMode;

    void readCSV();
    void saveToDatabase();

};

#endif // CSVIMPORTER_H
