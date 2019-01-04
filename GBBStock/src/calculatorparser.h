#ifndef CALCULATORPARSER_H
#define CALCULATORPARSER_H

#include <QString>
#include <QMap>
#include <QChar>
#include <QSet>
#include <QDebug>

class CalculatorParser
{
public:
    CalculatorParser();
    bool parseExpression(const QString &expr, const QSet<QString> &variables);

    QString getError() const {return error;}

private:

    typedef enum {PS_START,PS_GOT_NUMBER,PS_GOT_VAR,PS_REQUIRE_OP} ParseState;

    struct Node{
        QString op;
        QString variableName;
        qreal value;
        Node *right;
        Node *left;

        Node(){
            op = "";
            variableName = "";
            value = 0;
            right = nullptr;
            left = nullptr;
        }

    };

    QStringList tokens;
    QString error;


    // Functions
    bool isOperator(const QChar &c){ return (c == '-') || (c == '/') || (c == '*') || (c == '+'); }
    Node * parseNoParenthesisExpression(const QStringList &expr);

};

#endif // CALCULATORPARSER_H
