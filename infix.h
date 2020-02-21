/**
 * Recursive Decent Parser (RDP).
 * This one does infix expressions with parenthesis and the four basic operations.
 * It could easily be extended to support more operations.
 */

// Infix Declaration - infix.h
#include <string>

class Infix {
private:
    long pos;
    std::string expr;
    bool expect(std::string what);
    double number();
    double parenthesis();
    double multiply();
    double add();
    double expression();
public:
    enum class ParseError { VALUE, PARENTHESIS, OPERATOR };
    long getPos();
    double eval();
    double eval(std::string newExpression);
    Infix(std::string newExpression);
    Infix();
};
