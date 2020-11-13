#include "Parser.hpp"

Parser::Parser (Lexer *l) {
    lexer = l;
    move();
}

void Parser::move () {
    look = lexer->scan();
}

void Parser::match(int t) {
    if (t == int(look->tag)) 
        move();
    else 
        throw ("At line " + std::to_string(lexer->line) + " " + std::string(1, (char)t) + " expected, met " + look->toString() + "\n" );
}

Block *Parser::block() {
    match('{');
    auto block = new Block();

    while ((int)look->tag != '}') {
        Statement* stmt = statement();
        block->stmts.push_back( stmt );
    }

    match('}');
    return block;
}

Statement *Parser::statement() {
    if (look->tag == Tag::IF)
        return _if();
    if (look->tag == Tag::WHILE)
        return _while();
    if (look->tag == (Tag)'{') 
        return block();
    else 
        return assign();
}

Statement *Parser::assign() {
    Token *t = look;
    match((int)Tag::ID);
    Id *id = new Id(t);
    match('=');
    Expr *expr = boolean();
    match(';');
    return new Set(id, expr);
}

If *Parser::_if() {
    If* node = new If();
    match((int)Tag::IF);
        match('(');  
        node->expr = boolean(); 
        match(')');
    match((int)Tag::THEN);
        node->thenstmt = statement();
    match((int)Tag::ELSE);
        node->elsestmt = statement();
    return node;
}


While *Parser::_while() {
    While* node = new While();
    match((int)Tag::WHILE);
        match('(');  node->expr = expr();  match(')');
    match((int)Tag::THEN);
    node->stmt = statement();
    return node;
}

Expr *Parser::boolean()
{
    Expr* x = join();
    while( look->tag == Tag::OR ) {
        move(); x = new Or(x, join());
    }
    return x;
}

Expr *Parser::join()
{
    Expr* x = equality();
    while( look->tag == Tag::AND ) {
        move(); x = new And(x, equality());
    }
    return x;
}

Expr *Parser::equality()
{
    Expr* x = rel();
    while( look->tag == Tag::EQ || look->tag == Tag::NE) {
        Token *tok = look;
        move(); 
        x = new Rel(x, tok, rel());
    }
    return x;
}


Expr *Parser::rel()
{
    Expr* x = expr();
    Token *tok = look;

    switch ((int)look->tag) {
        case '<':
        case (int)Tag::LE:
        case (int)Tag::GE:
        case '>':
            move(); 
            return new Rel(x, tok, expr());
        default:
            return x;
    }
    return x;
}

Expr *Parser::expr() {
    Expr* x = term();
    while((int)look->tag == '+' || (int)look->tag == '-') {
        Token tok = *look; 
        move(); 
        x = new Arith(x, tok, term());
    }
    return x;
}

Expr *Parser::term() {
    Expr* x = unary();
    while((int)look->tag == '*' || (int)look->tag == '/') {
        Token tok = *look;
        move();
        x = new Arith(x, tok, unary());
    }
    return x;
}

Expr *Parser::unary() {
    if ((int)look->tag == '-') {
        move();
        return new Unary(Word::_minus, unary());
    } else if ((int)look->tag == '!') {
        Token t = *look;
        move();
        return new Unary(t, unary());
    }
    else return factor();
}

Expr *Parser::factor() {
    Expr* x = nullptr;
    switch((int)look->tag) {
        case '(':
            move(); 
            x = boolean(); 
            match(')');
            return x;
        case (int)Tag::NUM:
            x = new Constant(look); 
            move(); 
            return x;
        case (int)Tag::REAL:
            x = new Constant(look); 
            move(); 
            return x;
        case (int)Tag::ID:
            x = new Id(look); 
            move(); 
            return x;
        default: 
            throw ("syntax error in factor()");
    }
}


