#include "csvreader.h"

CSVReader::CSVReader()
{
    fieldDelimiter = ',';
    stringDelimiter = '"';
    enforceSameLengthLines = true;
    firstLineIsColumnNames = true;
}


bool CSVReader::loadCSV(const QString &filename){

    error = "";
    data.clear();
    columnNames.clear();

    QFile file(filename);
    if (!file.open(QFile::ReadOnly)){
        error = "No se pudo abrir el archivo " + filename;
        return false;
    }

    QTextStream reader(&file);
    reader.setCodec("UTF-8");

    while (!reader.atEnd()){
        QString line = reader.readLine();
        if (!parseLine(line)) {
            file.close();
            return false;
        }
    }

    file.close();

    // All good. Removing the first line as the header.
    if ((data.size() > 0) && (firstLineIsColumnNames)) {
        columnNames = data.first();
        data.removeFirst();
    }

    return true;

}

bool CSVReader::parseLine(const QString &line){

    QString value;
    QStringList row;
    ParseLineState pls = PLS_START;

    value = "";

    for (qint32 i = 0; i < line.size(); i++){

        switch (pls) {
        case PLS_START:
            if (line.at(i).isSpace()) continue;
            if (line.at(i) == fieldDelimiter){
                row << value; // This should be empty
            }
            else if (line.at(i) == stringDelimiter){
                pls = PLS_EXPECT_QUOTE;
            }
            else {
                // Any other char.
                pls = PLS_EXPECT_COMMA_NO_QUOTE;
                value = value + line.at(i);
            }
            break;
        case PLS_EXPECT_COMMA:
            if (line.at(i).isSpace()) continue;
            if (line.at(i) == fieldDelimiter){
                pls = PLS_START;
            }
            else{
                error = "There is no comman after ending quotes: " + line;
                return false;
            }
            break;
        case PLS_EXPECT_COMMA_NO_QUOTE:
            if (line.at(i) != fieldDelimiter){
                value = value + line.at(i);
            }
            else {
                row << value;
                value = "";
                pls = PLS_START;
            }
            break;
        case PLS_EXPECT_QUOTE:
            if (line.at(i) != stringDelimiter){
                value = value + line.at(i);
            }
            else {
                row << value;
                value = "";
                pls = PLS_EXPECT_COMMA;
            }
            break;
        }
    }

    // Adding the last one. Allways
    row << value;

    if (enforceSameLengthLines){
        if (data.size() > 0){
            if (data.last().size() != row.size()){
                error = "Last line (" + QString::number(data.size()-1) + ") had " + QString::number(data.last().size()) + " columns. Current line has: " + QString::number(row.size()) + ". Current line is: " + line;
                qWarning() << "DATA LAST" << data.last();
                qWarning() << "DATA ROW"  << row;
                return false;
            }
        }
    }

    // No problem adding row to data.
    data << row;

    return true;

}
