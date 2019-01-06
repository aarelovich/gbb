#ifndef CSVREADER_H
#define CSVREADER_H

#include <QFile>
#include <QTextStream>
#include <QDebug>

class CSVReader
{
public:
    CSVReader();
    void setEnforceSameLengthLines(bool enable) {enforceSameLengthLines = enable;}
    void setFirstLineIsColumnNames(bool enable) {firstLineIsColumnNames = enable; }
    bool loadCSV(const QString &filename);
    QString getError() const {return error;}
    QStringList getColumnNames() const {return columnNames;}
    QList<QStringList> getData() const {return data;}

private:

    bool enforceSameLengthLines;
    bool firstLineIsColumnNames;
    QChar fieldDelimiter;
    QChar stringDelimiter;

    typedef enum {PLS_START,PLS_EXPECT_QUOTE,PLS_EXPECT_COMMA,PLS_EXPECT_COMMA_NO_QUOTE} ParseLineState;

    QStringList columnNames;
    QList<QStringList> data;
    QString error;

    bool parseLine(const QString &line);

};

#endif // CSVREADER_H
