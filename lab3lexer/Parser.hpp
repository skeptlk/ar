#ifndef PARSER
#define PARSER
#include <iostream>
#include "Lexer.hpp"

class Parser {
private: 
    Lexer * lexer;
    void move();
    Token * look;
public: 
    Parser(Lexer * l);
    void parse();
};

#endif // PARSER