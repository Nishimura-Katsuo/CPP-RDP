/**
 * Recursive Decent Parser (RDP).
 * This one does infix expressions with parenthesis and the four basic operations.
 * It could easily be extended to support more operations.
 */


// Test the shits - main.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include "infix.h"

// Just a simple trimmer.
std::string trim(std::string orig) {
    int start = orig.find_first_not_of(' '), count = orig.find_last_not_of(' ') - start + 1;

    if (start >= 0 && count > 0) {
        return orig.substr(start, count);
    }

    return "";
}

int main() {
    Infix expr;
    std::string input = "";

    std::cout << "Enter an infix expression: ";
    std::getline(std::cin, input);
    input = trim(input);

    while (input.length()) {
        try {
            std::cout << input << " = " << expr.eval(input) << std::endl;
        } catch (Infix::ParseError msg) {
            switch(msg) {
                case Infix::ParseError::VALUE:
                    std::cout << "Value expected:" << std::endl;
                    break;
                case Infix::ParseError::PARENTHESIS:
                    std::cout << "Closing parenthesis expected:" << std::endl;
                    break;
                case Infix::ParseError::OPERATOR:
                    std::cout << "Operator expected:" << std::endl;
                    break;
                default:
                    std::cout << "Unknown parsing error:" << std::endl;
                    break;
            }
            std::cout << input << std::endl;
            std::cout << std::setw(static_cast<std::streamsize>(expr.getPos()) + 1) << '^' << std::endl;
        }
        std::cout << std::endl << "Enter an infix expression: ";
        std::getline(std::cin, input);
        input = trim(input);
    }
}
