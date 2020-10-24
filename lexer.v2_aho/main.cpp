#include <iostream>
#include <fstream>
#include "Tokens.hpp"
#include "Lexer.hpp"

int main() {

    std::ifstream input("data.txt");

    Lexer *lex = new Lexer(&input);

    lex->scan();

}