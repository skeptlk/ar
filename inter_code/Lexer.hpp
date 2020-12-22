#ifndef LEXER
#define LEXER

#include <iostream>
#include <sstream>
#include <map>
#include "Tokens.hpp"

class Lexer {
private: 
    char peek = ' ';
    std::stringstream *input;
    void reserve(Word* w);
    void readch();
    bool readch(char c);
public:
    static int line;
    bool iseof = false;
    Lexer();
    Token* scan();
    std::map<std::string, Token*> words;
    void nextline (std::string line);
};

#endif