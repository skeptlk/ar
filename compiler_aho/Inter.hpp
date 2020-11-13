#ifndef INTER
#define INTER
#include <string>
#include <iostream>
#include <exception>
#include "Tokens.hpp"
#include "Lexer.hpp"



class Node {
public:
    int lexline = 0;
    Node();
    void error(std::string s) {
        throw ("near line " + std::to_string(lexline) + ": " + s);
    }
    int newLabel();
    void emitlabel(int i);
    void emit(std::string s);

    static int labels;
};

class Expr: public Node {
public:
    Token op;
    Type type;
    Expr();
    Expr(Token tok, Type p);
    Expr* gen();
    Expr* reduce();
    void jumping(int t, int f);
    void emitjumps(std::string test, int t, int f);
    std::string toString();
};

class Id: public Expr {
public: 
    int offset;
    Id();
    Id(Word id, Type p, int b);
};

class Op: public Expr {
public:
    Op(Token tok, Type p);
    Expr* reduce();

};


#endif