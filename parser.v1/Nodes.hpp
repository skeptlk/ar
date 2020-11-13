#ifndef NODES
#define NODES
#include <iostream>
#include <vector>
#include "Lexer.hpp"
#include "Tokens.hpp"


class Node {
public: 
    int lexline;
    Node();
    virtual std::string toString();
};

class Expr: public Node {
public: virtual std::string toString();
};

class Or: public Expr {
public: Or(Expr* e1, Expr* e2);
        Expr* left;
        Expr* right;
        virtual std::string toString();
};

class And: public Expr {
public: And(Expr* e1, Expr* e2);
        Expr* left;
        Expr* right;
        virtual std::string toString();
};

class Rel: public Expr {
public: Rel(Expr* e1, Token* o, Expr* e2);
        Expr* left;
        Expr* right;
        Token *op;
        virtual std::string toString();
};

class Arith: public Expr {
public: 
    Arith(Expr* e1, Token o, Expr* e2);
    Expr* left;
    Expr* right;
    Token op; 
    virtual std::string toString();
};

class Unary: public Expr {
public: Unary(Token o, Expr *ex);
        Expr* expr;
        Token op;
        virtual std::string toString();
};

class Constant: public Expr {
public: Constant(Token *t);
        Token *tok;
        virtual std::string toString();
};

class Id: public Expr {
public: Id(Token *l);
        Token* label;
        virtual std::string toString();
};

class Statement : public Node {
public: Expr *expr;
        std::string toString();
        virtual std::vector<std::string> toString(int &w);
};

class If : public Statement {
public: Expr *expr;
        Statement *thenstmt, *elsestmt;
        std::string toString();
        virtual std::vector<std::string> toString(int &w);
};

class While : public Statement {
public: Expr *expr;
        Statement *stmt;
        std::string toString();
        virtual std::vector<std::string> toString(int &w);
};

class Block : public Statement {
public: 
    std::vector<Statement*> stmts;
    std::string toString();
    virtual std::vector<std::string> toString(int &w);
};

class Set: public Statement {
public: 
    Set(Id* i, Expr* ex);
    Id *id; 
    Expr *expr;
    std::string toString();
    virtual std::vector<std::string> toString(int &w);
};



#endif // NODES