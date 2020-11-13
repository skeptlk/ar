#include <iostream>
#include <fstream>
#include "Parser.hpp"
#include "Lexer.hpp"
#include "Tokens.hpp"

int main() {
    int test = 1;

    std::ifstream input("data.txt");
    Lexer *lex = new Lexer(&input);
    Parser *parser = new Parser(lex);

    try
    {
        Node *program = parser->block();
        std::cout << "=== OUTPUT: ===\n";
        std::cout << program->toString();
    }
    catch(std::string e)
    {
        std::cout << e << '\n';
    }
}