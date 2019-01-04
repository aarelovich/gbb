#include "calculatorparser.h"

CalculatorParser::CalculatorParser()
{

}

bool CalculatorParser::parseExpression(const QString &expr, const QSet<QString> &variables){

    error = "";
    tokens.clear();

    if (expr.isEmpty()){
        error = "La expresión no puede estar vacia";
        return false;
    }

    QString number = "";
    QString varlist = variables.toList().join(",");
    qint32 openedParenthesis = 0;
    qint32 closedParenthesis = 0;

    ParseState pstate = PS_START;

    for (qint32 i = 0; i < expr.size(); i++){

        if (expr.at(i).isSpace()){
            // Spaces are ignored.
            continue;
        }

        switch(pstate){
        case PS_START:
            if (expr.at(i).isDigit() || (expr.at(i) == '.')){
                number = number + expr.at(i);
                pstate = PS_GOT_NUMBER;
            }
            else if (expr.at(i) == '(') {
                tokens << expr.at(i);
                openedParenthesis++;
            }
            else if (variables.contains(expr.at(i))){
                tokens << expr.at(i);
                pstate = PS_GOT_VAR;
            }
            else {
                error = "Caracater incorrecto: " + QString(expr.at(i)) + " en la posición " + QString::number(i) + ". Deberia ser un numero, un ( o una variable: " + varlist;
                return false;
            }
            break;
        case PS_GOT_NUMBER:
            if (expr.at(i).isDigit() || (expr.at(i) == '.')){
                number = number + expr.at(i);
            }
            else if (expr.at(i) == ')') {
                if (number.at(0) == '.'){
                    number = "0" + number;
                }
                tokens << number << expr.at(i);
                number = "";
                closedParenthesis++;
                pstate = PS_REQUIRE_OP;
            }
            else if (isOperator(expr.at(i))){
                if (number.at(0) == '.'){
                    number = "0" + number;
                }
                tokens << number << expr.at(i);
                number = "";
                pstate = PS_START;
            }
            else {
                error = "Caracater incorrecto: " + QString(expr.at(i)) + " en la posición " + QString::number(i) + ". Deberia ser un numero, un operador +,-,/,* o un )";
                return false;
            }
            break;
        case PS_REQUIRE_OP:
            if (isOperator(expr.at(i))){
                tokens << expr.at(i);
                pstate = PS_START;
            }
            else if (expr.at(i) == ')') {
                tokens << expr.at(i);
                closedParenthesis++;
            }
            else {
                error = "Caracater incorrecto: " + QString(expr.at(i)) + " en la posición " + QString::number(i) + ". Deberia ser un operador: +,-,/,*";
                return false;
            }
            break;
        case PS_GOT_VAR:
            if (expr.at(i) == ')') {
                tokens << expr.at(i);
                closedParenthesis++;
                pstate = PS_REQUIRE_OP;
            }
            else if (isOperator(expr.at(i))){
                tokens << expr.at(i);
                pstate = PS_START;
            }
            else {
                error = "Caracater incorrecto: " + QString(expr.at(i)) + " en la posición " + QString::number(i) + ". Deberia ser un operador +,-,/,* o un )";
                return false;
            }
            break;
        }

    }

    // Checking if the last value was a number, and adding it to the list.
    if (!number.isEmpty()){
        if (number.at(0) == '.'){
            number = "0" + number;
        }
        tokens << number;
    }

    if (openedParenthesis != closedParenthesis){
        error = "Se abrieron " + QString::number(openedParenthesis) + " paréntesis y se cerraron " + QString::number(closedParenthesis);
        return false;
    }

    if (pstate == PS_START){
        error = "El ultimo caracter no puede ser un operador";
        return false;
    }

    qWarning() << tokens;

    return true;
}
