#include <iostream>
#include <fstream>
#include "Parser.hpp"
#include "Lexer.hpp"
#include "Tokens.hpp"

int main() {
    std::ifstream input("data.txt");
    Lexer *lex = new Lexer(&input);
    Parser *parser = new Parser(lex);

    parser->parse();
}