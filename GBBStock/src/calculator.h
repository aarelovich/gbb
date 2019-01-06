#ifndef CALCULATORPARSER_H
#define CALCULATORPARSER_H

#include <QString>
#include <QSet>
#include <QDebug>
#include <QScriptEngine>

class Calculator
{
public:
    Calculator();
    bool evaluateExpression(const QString &expr, const QMap<QString,qreal> variableValues);
    QString getError() const {return error;}
    qreal getResult() const {return result;}

private:
    QString error;
    qreal result;
};

#endif // CALCULATORPARSER_H
