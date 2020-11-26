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
    static int labels;
    Node() {
        lexline = Lexer::line;
    }
    void error(std::string s) {
        throw ("near line " + std::to_string(lexline) + ": " + s);
    }
    int newLabel() {
        return ++labels;
    }
    void emitlabel(int i) {
        std::cout << "L" << i << ":";
    }
    void emit(std::string s) {
        std::cout << "\t" << s;
    }
    virtual std::string toString();
};

int Node::labels = 0;


class Expr: public Node {
public:
    Token *op;
    Type *type;
    Expr() {};
    Expr(Token *tok, Type *p) {
        op = tok;
        type = p;
    }
    Expr* gen() { return this; }
    Expr* reduce() { return this; }
    void jumping(int t, int f) { 
        emitjumps(toString(), t, f); 
    }
    void emitjumps(std::string test, int t, int f) {
        if (t != 0 && f != 0) {
            emit("if " + test + " goto L" + std::to_string(t));
            emit("goto L" + std::to_string(f));
        }
        else if (t != 0)
            emit("if " + test + " goto L" + std::to_string(t));
        else if (f != 0)
            emit("iffalse " + test + " goto L" + std::to_string(f));
        else ; // nothing since both t and f fall through
    }
    virtual std::string toString() {
        return op->toString();
    }
};

class Id: public Expr {
public: 
    int offset; // relative address
    Id() { }
    Id(Word *id, Type *p, int b): Expr(id, p) {
        offset = b;
    }
};

class Op: public Expr {
public:
    Op(Token *tok, Type *p): Expr(tok, p) {}
    Expr* reduce() {
        Expr* x = gen();
        Temp *t = new Temp(type);
        emit(t->toString() + " = " + x->toString());
        return t;
    }
};

class Arith: public Op {
public:
    Expr *expr1, *expr2;
    Arith(Token *tok, Expr *x1, Expr *x2): Op(tok, nullptr) {
        expr1 = x1;
        expr2 = x2;
        type = Type::max(expr1->type, expr2->type);
        if (type == nullptr)
            error("type error");
    }
    Expr * gen() {
        return new Arith(op, expr1->reduce(), expr2->reduce());
    }
    virtual std::string toString() {
        return expr1->toString() + " " + op->toString() + " " + expr2->toString();
    }
};


class Temp: public Expr {
public:
    static int count;
    int number = 0;
    Temp(Type *p): Expr(&Word::_temp, p) {
        number = ++count;
    }
    virtual std::string toString() {
        return "t" + std::to_string(number);
    }
};

int Temp::count = 0;

class Unary: public Op {
public:
    Expr * expr;
    Unary(Token *tok, Expr *x): Op(tok, nullptr) {
        expr = x;
        type = Type::max(&Type::_int, expr->type);
        if (type == nullptr) error("type error");
    }
    Expr * gen() {
        return new Unary(op, expr->reduce());
    }
    virtual std::string toString() {
        return op->toString() + " " + expr->toString();
    }
};

class Constant: public Expr {
public:
    Constant(Token *tok, Type *p): Expr(tok, p) {}
    Constant(int i): Expr(new Num(i), &Type::_int) {}
    void jumping(int t, int f) {
        if (this == &_true && t != 0)
            emit("goto L" + std::to_string(t));
        else if (this == &_false &&  f != 0)
            emit("goto L" + std::to_string(f));
    }

    static Constant _true, _false;
};

Constant Constant::_true  = Constant(&Word::_true,  &Type::_bool);
Constant Constant::_false = Constant(&Word::_false, &Type::_bool);


class Logical: public Expr {
public: 
    Expr *expr1, *expr2;

    Logical(Token *tok, Expr *x1, Expr *x2): Expr(tok, nullptr) {
        expr1 = x1;
        expr2 = x2;
        type = check(expr1->type, expr2->type);
        if (type == nullptr) 
            error("type error");
    }
    Type * check(Type *p1, Type *p2) {
        if (p1 == &Type::_bool && p2 == &Type::_bool)
            return &Type::_bool;
        else return nullptr;
    }
    Expr * gen() {
        int f = newLabel();
        int a = newLabel();
        Temp *temp = new Temp(type);
        jumping(0, f);
        emit(temp->toString() + " = true");
        emit("goto L" + std::to_string(a));
        emitlabel(f);
        emit(temp->toString() + " = false");
        emitlabel(a);
        return temp;
    }
    virtual std::string toString() {
        return expr1->toString() + " " + op->toString() + " " + expr2->toString();
    }
};

class Or: public Logical {
public: 
    Or(Token * tok, Expr *x1, Expr *x2): Logical(tok, x1, x2) {}
    void jumping(int t, int f) {
        int label = t != 0 ? t : newLabel();
        expr1->jumping(label, 0);
        expr2->jumping(t, f);
        if (t == 0)
            emitlabel(label);
    }
};



#endif