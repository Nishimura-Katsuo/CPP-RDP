/**
 * Recursive Decent Parser (RDP).
 * This one does infix expressions with parenthesis and the four basic operations.
 * It could easily be extended to support more operations.
 */

// Boring definition shits - infix.cpp
#include <string>
#include "infix.h"

// Utility function.
bool Infix::expect(std::string what) {
    // Trim beginning spaces, because we don't need them.
    while (expr[pos] == ' ') {
        pos++;
    }

    if (expr[pos]) { // NULL character... no point in checking.
        for(long c = 0; what[c]; c++) {
            if (expr[pos] == what[c]) {
                return true;
            }
        }
    }

    return false;
}

// The beginning of the actual parser.
// It starts bigger and 'decends' into smaller rules.

double Infix::expression() {
    // Call our lowest priority operation.
    return add();
}

double Infix::add() {
    // Calling our next highest rule here allows it to process before add does anything.
    // This respects order of operations.
    double a = multiply(), b;
    char op;
    if (expect("+-")) {
        op = expr[pos++];
        // Calling add again here allows us to chain operations together.
        // IE: 1 + 2 + 3
        b = add();
        if (op == '+') {
            return a + b;
        } else {
            return a - b;
        }
    }

    return a;
}

double Infix::multiply() {
    // Calling the next higher operation to respect order of operations.
    double a = parenthesis(), b;
    char op;
    if (expect("*/")) {
        op = expr[pos++];
        // Allows chaining by calling itself here.
        b = multiply();
        if (op == '*') {
            return a * b;
        } else {
            return a / b;
        }
    }

    return a;
}

double Infix::parenthesis() {
    double ret;
    if (expect("(")) {
        pos++;
        // Look! It restarts the parsing from the top again. :)
        // This is where RDP really shines. It can parse sub-expressions
        // of itself.
        ret = expression();

        if (expect(")")) {
            pos++;
        } else {

            throw ParseError::PARENTHESIS;
        }
    } else {
        ret = number();
    }

    return ret;
}

double Infix::number() {
    // Trim beginning spaces, because we don't need them.
    while (expr[pos] == ' ') {
        pos++;
    }

    // Number is the last thing to look for. Nothing has higher priority
    // than a number.

    long start = pos;

    while (expr[pos] >= '0' && expr[pos] <= '9') {
        pos++;
    }
    if (expr[pos] == '.') {
        pos++;
        while (expr[pos] >= '0' && expr[pos] <= '9') {
            pos++;
        }
    }

    if (start == pos) {
        throw ParseError::VALUE;
    }

    return stof(expr.substr(start, pos - start));

}

// Basic setters/invokers.
long Infix::getPos() {
    return pos;
}

double Infix::eval() {
    pos = 0;
    double ret = expression();
    // Trim ending spaces, because we don't need them.
    while (expr[pos] == ' ') {
        pos++;
    }

    if (pos != expr.length()) {
        throw ParseError::OPERATOR;
    }
    return ret;
}

double Infix::eval(std::string newExpression) {
    expr = newExpression;
    return eval();
}

Infix::Infix(std::string newExpression) {
    expr = newExpression;
}

Infix::Infix() {
    expr = "";
}
