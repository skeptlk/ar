#include "Nodes.hpp"

std::string asciiBoxTop(int w) {
    std::string str = "┌";
    for (int i = 1; i < w; i++)
        str += "─";
    str += "┐";
    return str;
}

std::string asciiBoxBottom(int w) {
    std::string str = "└";
    for (int i = 1; i < w; i++)
        str += "─";
    str += "┘";
    return str;
}


Node::Node() 
{ lexline = Lexer::line; }

std::string Node::toString () {
    return "you're not supposed to see this";
}

std::string Expr::toString () {
    return "you're not supposed to see this";
}

Or::Or(Expr* e1, Expr* e2) 
{ left = e1; right = e2; }

std::string Or::toString()
{
    return left->toString() + " || " + right->toString();
}


And::And(Expr* e1, Expr* e2) 
{ left = e1; right = e2; }

std::string And::toString()
{
    return left->toString() + " && " + right->toString();
}


Rel::Rel(Expr* e1, Token *o, Expr* e2) 
{ left = e1; op = o; right = e2; }

std::string Rel::toString()
{
    return left->toString() + " " + op->toString() + " " + right->toString();
}


Arith::Arith(Expr* e1, Token o, Expr* e2) 
{ left = e1; right = e2; op = o; }

std::string Arith::toString () 
{
    return left->toString() + " " + op.toString() + " " + right->toString();
}


Unary::Unary(Token o, Expr *ex) 
{ expr = ex; op = o; }

std::string Unary::toString () 
{
    return op.toString() + expr->toString();
}


Constant::Constant(Token *t) 
{ tok = t; }

std::string Constant::toString () 
{
    return tok->toString();
}


Id::Id(Token *l) 
{
    label = l; 
}

std::string Id::toString ()
{
    return label->toString();
}


std::string Statement::toString() 
{
    return "";
}

std::vector<std::string> Statement::toString(int &w)
{
    std::vector<std::string> result;
    result.push_back("<statement>");
    w = 11;
    return result;
}

std::string Block::toString() {
    int _;
    std::string result;
    std::vector<std::string> tmp = toString(_);
    for (std::string s: tmp)
        result += s + "\n";

    result += "\n";
    return result;
}

std::vector<std::string> Block::toString(int &w)
{
    std::vector<std::string> result;
    int wmax = -1;

    for (Statement *stmt : stmts) {
        // concatenate vectors and determine max width
        std::vector<std::string> tmp = stmt->toString(w);
        result.insert(result.end(), tmp.begin(), tmp.end());
        wmax = std::max(w, wmax);
    }

    if (stmts.size() == 0) {
        result.push_back("<empty>"); wmax = 7;
    }

    w = wmax;
    return result;
}

Set::Set(Id* i, Expr* ex) 
{ id = i; expr = ex; }

std::string Set::toString()
{
    return "<set>";
}

std::vector<std::string> Set::toString(int &w)
{
    std::vector<std::string> result;
    std::string str = id->toString() + " = " + expr->toString();
    w = str.length() + 3;
    result.push_back(asciiBoxTop(w));
    result.push_back("│ " + str + " │");
    result.push_back(asciiBoxBottom(w));
    return result;
}

std::string If::toString() {
    return "<->";
}

std::vector<std::string> If::toString(int &_w) {
    std::vector<std::string> result, thenblock, elseblock;
    std::string thenstr, elsestr;
    int w = -1, wmax = -1, tmp;

    thenstr = "IF (" + expr->toString() + ") THEN: ";
    elsestr = "ELSE:";
    wmax = std::max(w, (int)thenstr.length());

    thenblock = thenstmt->toString(w);
    wmax = std::max(w, wmax);
    elseblock = elsestmt->toString(w);
    wmax = std::max(w, wmax);
    
    // build result vector
    wmax += 4;
    result.push_back(asciiBoxTop(wmax));
    result.push_back("| " + thenstr + std::string(wmax - thenstr.length() - 4, ' ') + " |");
    for (std::string s : thenblock) {
        result.push_back("| " + s);
    }
    result.push_back("| " + elsestr);
    for (std::string s : elseblock) {
        result.push_back("| " + s);
    }
    result.push_back(asciiBoxBottom(wmax));
    _w = wmax;

    
    return result;
}

std::string While::toString() {
    return "<->";
}

std::vector<std::string> While::toString(int &w) {
    std::vector<std::string> result;
    return result;
}

