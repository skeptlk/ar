#ifndef PARSER
#define PARSER
#include <iostream>
#include "Lexer.hpp"
#include "Nodes.hpp"


class Parser {
private: 
    Lexer * lexer;
    void move() {
        look = lexer->scan();
    }
    void match(int t);
    Token * look;
public: 
    Parser(Lexer * l);
    Block *block();
    If *_if();
    While *_while();
    Statement *statement();
    Statement *assign();
    Expr *expr();
    Expr *boolean();
    Expr *join();
    Expr *equality();
    Expr *rel();
    Expr *term();
    Expr *unary();
    Expr *factor();

};

#endif // PARSER