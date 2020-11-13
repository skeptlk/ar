#include "Inter.hpp"

/**
 *      NODE
 */

int Node::labels = 0;

Node::Node() {
    lexline = Lexer::line;
}

void Node::error(std::string s) {
    throw ("near line " + std::to_string(lexline) + ": " + s);
}

int Node::newLabel() {
    return ++labels;
}

void Node::emitlabel(int i) {
    std::cout << "L" << i << ":";
}

void Node::emit(std::string s) {
    std::cout << "\t" << s;
}

/**
 *      EXPR
 */

Expr::Expr() {};

Expr::Expr(Token tok, Type p) {
    op = tok;
    type = p;
}

Expr* Expr::gen() {
    return this;
}

Expr* Expr::reduce() {
    return this;
}

void Expr::jumping(int t, int f) {
    emitjumps(toString(), t, f);
}

void Expr::emitjumps(std::string test, int t, int f) {
    if (t != 0 && f != 0) {
        emit("if " + test + " goto L" + std::to_string(t));
        emit("goto L" + std::to_string(f));
    }
    else if (t != 0)
        emit("if " + test + " goto L" + std::to_string(t));
    else if (f != 0)
        emit("iffalse " + test + " goto L" + std::to_string(f));
    else ;
}

std::string Expr::toString() {
    return op.toString();
}

/**
 *      ID
 */

Id::Id() { }

Id::Id(Word id, Type p, int b): Expr(id, p) {
    offset = b;
}

/**
 *      OP
 */

Op::Op(Token tok, Type p):Expr(tok, p) 
{}

Expr* Op::reduce()
{
    Expr* x = gen();
    Temp t = new Temp(type);
    emit(t.toString() + " = " + x->toString());
    return t;
}

