#include "csvimporter.h"

CSVImporter::CSVImporter()
{
    db = nullptr;
}


void CSVImporter::run(){
    if (prepareMode) readCSV();
    else saveToDatabase();
}

//-------------------------- Reading the CSV and preparing the input. Then sorting between update and append.

void CSVImporter::readCSV(){

    tUpdates.clear();
    emit(updateProgress(0));

    CSVReader csvreader;
    if (!csvreader.loadCSV(csvFile)){
        for (qint32 i = 0; i < csvreader.getData().size(); i++){
            std::cout << "ROW " << i << ": ";
            for (qint32 j = 0; j < csvreader.getData().at(i).size(); j++){
                std::cout << csvreader.getData().at(i).at(j).toStdString() << " | ";
            }
            std::cout << std::endl;
        }
        errorLog("Importing a CSV: " + csvreader.getError());
        error = "Ha ocurrido un problema importando el CSV\nContactarse con Ariel Arelovich: aarelovich@gmail.com";
        return;
    }

    QSet<QString> intColumns;
    QSet<QString> floatColumns;
    QSet<QString> textColumns;
    intColumns   << TSTOCK_COL_COL << TSTOCK_COL_ESTANTE << TSTOCK_COL_STOCK_D
                 << TSTOCK_COL_STOCK_F << TSTOCK_COL_STOCK_MIN_D << TSTOCK_COL_STOCK_MIN_F;
    floatColumns << TSTOCK_COL_COST << TSTOCK_COL_COSTM << TSTOCK_COL_COSTP;
    textColumns  << TSTOCK_COL_NOMBRE_ALT << TSTOCK_COL_DESC << TSTOCK_COL_LOCAT << TSTOCK_COL_TIPO_PROD << TSTOCK_COL_MARCA;


    QStringList columnNames = csvreader.getColumnNames();
    QList<QStringList> csv = csvreader.getData();

    // Eliminating all the spaces from the product name and making all letters uppercase
    qint32 product_index = columnNames.indexOf(TSTOCK_COL_PRODUCTO);
    if (product_index == -1){
        error = "La matriz no tiene una columna de nombre producto. No es posible seguir";
        return;
    }

    qint32 brand_index = columnNames.indexOf(TSTOCK_COL_MARCA);
    if (brand_index == -1){
        error = "La matriz no tiene una columna de marca producto. No es posible seguir";
        return;
    }

    qint32 ptype_index = columnNames.indexOf(TSTOCK_COL_TIPO_PROD);
    if (brand_index == -1){
        error = "La matriz no tiene una columna de tipo de producto. No es posible seguir";
        return;
    }

    qint32 env_index = columnNames.indexOf(TSTOCK_COL_ENV);
    if (env_index == -1){
        error = "La matriz no tiene una columna de tipo de envase. No es posible seguir";
        return;
    }

    if (columnNames.indexOf(TSTOCK_COL_COST) == -1){
        error = "La matriz no tiene una columna de costo. No es posible seguir";
        return;
    }

    QStringList keyidCol; keyidCol << TSTOCK_COL_KEYID;

    for (qint32 i = 0; i < csv.size(); i++){

        QStringList row = csv.at(i);

        if (row.at(product_index).isEmpty()) continue;

        // Unifying the product name and brand names.
        QString prodname = cleanUpUniquetName(row.at(product_index));
        row[product_index] = prodname;

        QString brand = cleanUpUniquetName(row.at(brand_index));
        row[brand_index] = brand;

        QString prodtype = cleanUpUniquetName(row.at(ptype_index));
        row[ptype_index] = prodtype;

        QString recipient = cleanUpUniquetName(row.at(env_index),true);
        row[env_index] = recipient;

        // Checking for existance of the pair brand and product name.
        QString condition = QString(TSTOCK_COL_MARCA) + "='" + brand + "' AND "
                          + QString(TSTOCK_COL_PRODUCTO) + " = '" + prodname + "' AND "
                          + QString(TSTOCK_COL_ENV) + " = '" + recipient + "' AND "
                          + QString(TSTOCK_COL_TIPO_PROD) + " = '" + prodtype + "'";
        if (!db->readFromDB(TABLE_STOCK,keyidCol,condition)){
            errorLog("Checking DB for Existing pair: (" + brand + "," + prodname + "): " + db->getError());
            error = "Ha fallado la operación. No se han realizados cambios\nContactarse con Ariel Arelovich: aarelovich@gmail.com";
            return;
        }

        QString keyid = "-1";
        if (db->getLastResult().rows.size() > 0){
            if (db->getLastResult().rows.first().size() > 0){
                keyid = db->getLastResult().rows.first().first();
            }
        }

        TableUpdateStruct toupdate;
        toupdate.condition = "";

        //qWarning() << "Leyendo columna " << i << " and keyid is " << keyid;

        // Preprocessing is done depending on whether this is an update or not.
        if (keyid != "-1"){
            // Processing for update
            // Making sure that numbers ARE effectively numbers, and that text do no contain parenthesis. However if a column is empty, it left as is.
            toupdate.condition = QString(TSTOCK_COL_KEYID) + " = '" + keyid + "'";

            for (qint32 j = 0; j < columnNames.size(); j++){

                // Empty columns are ignored.
                if (row.at(j).isEmpty()) continue;

                if (intColumns.contains(columnNames.at(j))){
                    qint32 value = row.at(j).toInt();
                    row[j] = QString::number(value);
                }
                else if (floatColumns.contains(columnNames.at(j))){
                    qreal value = row.at(j).toDouble();
                    row[j] = QString::number(value);
                }
                else if (textColumns.contains(columnNames.at(j))){
                    QString value = row.at(j);
                    value = value.replace("(","--");
                    value = value.replace(")","--");
                    row[j] = value;
                }

                // Only non empty columns are updated.
                toupdate.columns << columnNames.at(j);
                toupdate.values << row.at(j);
            }
        }
        else{
            // Processing for insert
            // Making sure that numbers ARE effectively numbers, and that text do no contain parenthesis.
            for (qint32 j = 0; j < columnNames.size(); j++){
                if (intColumns.contains(columnNames.at(j))){
                    qint32 value = row.at(j).toInt();
                    row[j] = QString::number(value);
                }
                else if (floatColumns.contains(columnNames.at(j))){
                    qreal value = row.at(j).toDouble();
                    row[j] = QString::number(value);
                }
                else if (textColumns.contains(columnNames.at(j))){
                    QString value = row.at(j);
                    value = value.replace("(","--");
                    value = value.replace(")","--");
                    row[j] = value;
                }
            }
            toupdate.columns = columnNames;
            toupdate.values = row;
        }

        // Each row is added with the information to either be an update or an insert.
        tUpdates << toupdate;

        qreal p = (i+1)*100;
        p = p/csv.size();
        emit(updateProgress(p));

    }

    // Done.
    emit(updateProgress(0));

}


//-------------------------- Storing information in DB.

void CSVImporter::saveToDatabase(){

    emit(updateProgress(0));

    for (qint32 i = 0; i < tUpdates.size(); i++){
        if (tUpdates.at(i).condition.isEmpty()){
            if (!db->insertDB(TABLE_STOCK,tUpdates.at(i).columns,tUpdates.at(i).values)){
                errorLog("Inserting new product into DB: " + db->getError());
                error = "Ha fallado la operación. No se han realizados cambios\nContactarse con Ariel Arelovich: aarelovich@gmail.com";
                return;
            }
        }
        else{
            if (!db->updateDB(TABLE_STOCK,tUpdates.at(i).columns,tUpdates.at(i).values,tUpdates.at(i).condition)){
                errorLog("Inserting new product into DB: " + db->getError());
                error = "Ha fallado la operación. No se han realizados cambios\nContactarse con Ariel Arelovich: aarelovich@gmail.com";
                return;
            }
        }

        qreal p = (i+1)*100;
        p = p/tUpdates.size();
        emit(updateProgress(p));
    }

    emit(updateProgress(0));

}

//-------------------------- Getting the information as product updates.

QList<ProductInfo> CSVImporter::getProductList(bool lookForUpdates) const {

    QStringList reqInfo; reqInfo << TSTOCK_COL_PRODUCTO << TSTOCK_COL_MARCA << TSTOCK_COL_TIPO_PROD << TSTOCK_COL_COST << TSTOCK_COL_ENV;

    QList<ProductInfo> ans;

    for (qint32 i = 0; i < tUpdates.size(); i++){

        ProductInfo info;

        // This will filter updates when not looking for them
        if (!tUpdates.at(i).condition.isEmpty() && !lookForUpdates) continue;

        // This will filter new products when looking for updates
        if (tUpdates.at(i).condition.isEmpty() && lookForUpdates) continue;

        for (qint32 j = 0; j < reqInfo.size(); j++){
            qint32 index = tUpdates.at(i).columns.indexOf(reqInfo.at(j));
            QString val = "";
            if (index != -1){
                // This should always be true
                val = tUpdates.at(i).values.at(index);
            }
            info[reqInfo.at(j)] = val;
        }

        ans << info;

    }

    return ans;
}


