#include <iostream>
#include <fstream>
#include "Tokens.hpp"
#include "Env.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"


int main() {
    try {
        std::ifstream input("data.txt");
        Lexer * lex = new Lexer(&input);
        Parser * parse = new Parser(lex);
        parse->program();
    }
    catch(std::string e)
    {
        std::cout << e << '\n';
    }
}
