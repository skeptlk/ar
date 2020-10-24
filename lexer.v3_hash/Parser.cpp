#include "Parser.hpp"

Parser::Parser (Lexer *l) {
    lexer = l;
}

void Parser::move () {
    look = lexer->scan();
}

void Parser::parse() {
    int t;
    while (!lexer->iseof) {
        move();
    }
    lexer->printTable();
}

