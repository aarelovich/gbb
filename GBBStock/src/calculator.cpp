#include "calculator.h"

Calculator::Calculator()
{

}

bool Calculator::evaluateExpression(const QString &expr, const QMap<QString,qreal> variableValues){

    QString calculatorStringFunction;
    QStringList vars = variableValues.keys();

    if (variableValues.isEmpty()){
        calculatorStringFunction = "(function(){ return " + expr + ";})";
    }
    else{
        calculatorStringFunction = "(function(" + vars.join(",")  + "){ return " + expr + ";})";
    }

    QScriptSyntaxCheckResult syntaxCheck = QScriptEngine::checkSyntax(calculatorStringFunction);

    //qWarning() << "Checking the syntax" << calculatorStringFunction << "got" << syntaxCheck.state();

    if (syntaxCheck.state() != QScriptSyntaxCheckResult::Valid){
        error = syntaxCheck.errorMessage();
        return false;
    }

    QScriptEngine calculator;
    QScriptValue calcFunction = calculator.evaluate(calculatorStringFunction);
    QScriptValueList args;
    for (qint32 i = 0; i < vars.size(); i++){
        args << variableValues.value(vars.at(i));
    }

    QScriptValue scriptRes = calcFunction.call(QScriptValue(),args);
    result = scriptRes.toNumber();

    //() << "Result is" << result << (result == result);

    if (!(result == result)) {
        error = "Result was a NaN";
        return false;
    }
    return true;
}

