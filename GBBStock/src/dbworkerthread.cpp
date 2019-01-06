#include "dbworkerthread.h"

DBWorkerThread::DBWorkerThread()
{

}

void DBWorkerThread::run(){
    result = true;
    switch (dbo) {
    case DBO_APPLY_FORMULAS:
        wrongSyntax.clear();
        applyFormulas(true);
        applyFormulas(false);
        break;
    case DBO_RESTORE_DB:
        result = db->restoreBKP(restoreFile);
        break;
    }
}


void DBWorkerThread::applyFormulas(bool isPublic){

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
    condition = "(" + formulaCol + "<>'')";
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
