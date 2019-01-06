#include "dbworkerthread.h"

DBWorkerThread::DBWorkerThread()
{

}

void DBWorkerThread::run(){
    result = true;
    switch (dbo) {
    case DBO_APPLY_FORMULAS:
        wrongSyntax.clear();
        applyCostFormulas(true);
        applyCostFormulas(false);
        break;
    case DBO_MOD_FIELD_VALUE:
        modFieldWithValue();
        break;
    case DBO_MOD_FIELD_WITH_FORMULA:
        applyFormulaToField();
        break;
    case DBO_RESTORE_DB:
        result = db->restoreBKP(restoreFile);
        break;
    }
}

void DBWorkerThread::applyCostFormulas(bool isPublic){

    QString formulaCol;
    QString valueCol;
    if (isPublic){
        formulaCol = TSTOCK_COL_FORMULA_P;
        valueCol   = TSTOCK_COL_COSTP;
    }
    else{
        formulaCol = TSTOCK_COL_FORMULA_M;
        valueCol   = TSTOCK_COL_COSTM;
    }

    // Formulas for public cost.
    QStringList columns;
    columns << TSTOCK_COL_KEYID << formulaCol << TSTOCK_COL_COST;
    QString condition;
    condition = "(" + formulaCol + "<>'') AND (" + QString(TSTOCK_COL_BORRADO) + " ='0')";
    if (!keyidSubset.isEmpty()){
        condition = condition + " AND " + QString(TSTOCK_COL_KEYID) + " IN ('" + keyidSubset.join("', '") + "')";
    }
    if (!db->readFromDB(TABLE_STOCK,columns,condition)){
        errorLog("Reading Price P Formulas: " + db->getError());
        result = false;
        return;
    }

    DBData res = db->getLastResult();

    //qWarning() << "Formulas no vacias" << res.rows.size();

    // Applying the formulas
    Calculator calc;
    QMap<QString,qreal> vars;
    QStringList values;
    columns.clear();
    columns << valueCol;

    for (qint32 i = 0; i < res.rows.size(); i++){
        if (res.rows.at(i).size() == 3){
            vars["x"] = res.rows.at(i).at(2).toDouble();
            if (!calc.evaluateExpression(res.rows.at(i).at(1),vars)){
                wrongSyntax <<  res.rows.at(i).at(1);
            }
            else{
                // All good. Adding to the DB.
                //qWarning() << "Actualizando" << res.rows.at(i).at(0);
                condition = QString(TSTOCK_COL_KEYID) + "= '" + res.rows.at(i).at(0) + "'";
                values.clear(); values << QString::number(calc.getResult());
                if (!db->updateDB(TABLE_STOCK,columns,values,condition)){
                    errorLog("Updating Price P Formulas: " + db->getError());
                    result = false;
                    return;
                }
            }
        }
    }

}

void DBWorkerThread::applyFormulaToField(){

    // Getting the values where the formula will be applied.
    QStringList columns;
    columns << TSTOCK_COL_KEYID << operationColumn;
    QString condition = "(" + QString(TSTOCK_COL_BORRADO) + " ='0')";
    if (!keyidSubset.isEmpty()){
        condition = QString(TSTOCK_COL_KEYID) + " IN ('" + keyidSubset.join("', '") + "')";
    }
    if (!db->readFromDB(TABLE_STOCK,columns,condition)){
        errorLog("Reading Values to apply formula: " + db->getError());
        result = false;
        return;
    }

    DBData res = db->getLastResult();

    // Applying the formulas
    Calculator calc;
    QMap<QString,qreal> vars;
    QStringList values;
    columns.clear();
    columns << operationColumn;

    for (qint32 i = 0; i < res.rows.size(); i++){
        if (res.rows.at(i).size() != 2) continue;

        vars["x"] = res.rows.at(i).at(1).toDouble();
        if (!calc.evaluateExpression(fieldValue,vars)){
            wrongSyntax << fieldValue;
            continue;
        }

        // All good. Adding to the DB.
        condition = QString(TSTOCK_COL_KEYID) + "= '" + res.rows.at(i).at(0) + "'";
        values.clear(); values << QString::number(calc.getResult());
        if (!db->updateDB(TABLE_STOCK,columns,values,condition)){
            errorLog("Updating " + operationColumn + " with formula: " + db->getError());
            result = false;
            return;
        }
    }

}

void DBWorkerThread::modFieldWithValue(){

    //qWarning() << "Modding field" << operationColumn << "with value" << fieldValue << "on subset" << keyidSubset;

    QStringList columnToModify;
    columnToModify << operationColumn;
    QString condition = "(" + QString(TSTOCK_COL_BORRADO) + " ='0')";
    if (!keyidSubset.isEmpty()){
        condition = condition + " AND " + QString(TSTOCK_COL_KEYID) + " IN ('" + keyidSubset.join("', '") + "')";
    }
    QStringList values; values << fieldValue;
    if (!db->updateDB(TABLE_STOCK,columnToModify,values,condition)){
        errorLog("Updating " + operationColumn + " with value: " + fieldValue + ": " + db->getError());
        result = false;
        return;
    }

}
