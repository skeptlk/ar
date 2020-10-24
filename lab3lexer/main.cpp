#include <iostream>
#include <fstream>
#include "Tokens.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int main() 
{
    std::ifstream input("data.txt");
    Lexer *lex = new Lexer(&input);
    Parser *parser = new Parser(lex);

    parser->parse();
}