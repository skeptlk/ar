#include "Parser.hpp"

Parser::Parser (Lexer *l) {
    lexer = l;
}

void Parser::move () {
    look = lexer->scan();
}

void Parser::parse() {
    while (!lexer->iseof) {
        move();
    }
    std::cout << lexer->outp;
    lexer->printTable();
}

