#ifndef GLOBAL_H
#define GLOBAL_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>


//------------------------- Error File
#define APP_VERSION "1.0.0"

//------------------------- Error File
#define LOG_FILE    "logfile.log"

//------------------------- DB Connection Parameters
#define DB_NAME     "gbbdb"
#define DB_USER     "root"
#define DB_PASSWD   "2019gbbdb"
#define DB_HOST     "localhost"
#define DB_PORT     3306

//------------------------- Product Structure.
typedef QMap<QString,QString> ProductInfo;

//------------------------- DB Data structure
struct DBData{
    QStringList columns;
    QString error;
    QList<QStringList> rows;
    void clear(){
        columns.clear();
        rows.clear();
        error = "";
    }
    QString joinRowsAndCols(const QString &rowSep, const QString &colSep){
        QStringList compactedrows;
        for (qint32 i = 0; i < rows.size(); i++){
            compactedrows << rows.at(i).join(colSep);
        }
        return compactedrows.join(rowSep);
    }
    void fillRowsFromString(const QString &data, const QString &rowSep, const QString &colSep){
        QStringList crows = data.split(rowSep);
        for (qint32 i= 0; i < crows.size(); i++){
                rows << crows.at(i).split(colSep);
        }
    }
    void debugColumns() const{
        qWarning() << "COLUMNS" << columns;
        for (int i = 0; i < rows.size(); i++){
            qWarning() << " ROW:" << i << rows.at(i) << "Row Size: " << rows.size();
        }
    }
};

//-------------------- COLUMNS
#define TSTOCK_COL_KEYID           "keyid"
#define TSTOCK_COL_CODIGO          "codigo"
#define TSTOCK_COL_COD_ALT         "codigo_alt"
#define TSTOCK_COL_DESC            "descripcion"
#define TSTOCK_COL_COST            "costo"
#define TSTOCK_COL_COSTP           "costo_publico"
#define TSTOCK_COL_COSTM           "costo_mayorista"
#define TSTOCK_COL_STOCK_D         "stock_deposito"
#define TSTOCK_COL_STOCK_F         "stock_frente"
#define TSTOCK_COL_LOCAT           "ubicacion"
#define TSTOCK_COL_COL             "columna"
#define TSTOCK_COL_ESTANTE         "estante"
#define TSTOCK_COL_MARCA           "marca"
#define TSTOCK_COL_TIPO_PROD       "tipo_producto"
#define TSTOCK_COL_ENV             "envase"
#define TSTOCK_COL_STOCK_MIN_D     "minstock_deposito"
#define TSTOCK_COL_STOCK_MIN_F     "minstock_frente"


#define TVENTAS_COL_FECHA          "fecha"
#define TVENTAS_COL_KEYID          "keyid"
#define TVENTAS_COL_PROD           "tipo_producto"
#define TVENTAS_COL_PDFFAC         "pdf_factura"

#define FLAG_ISNEW                 "flag_is_new"

//-------------------- LOG Functions
static inline void errorLog(const QString &logmsg){
    QFile file(LOG_FILE);
    if (!file.open(QFile::Append)) return;

    QString s = QDateTime::currentDateTime().toString("dd/MM/yyyy - hh:mm:ss");
    s = s + ". " + logmsg;

    QTextStream writer(&file);
    writer.setCodec("UTF-8");
    writer << s << "\n";
    file.close();
}

#endif // GLOBAL_H
