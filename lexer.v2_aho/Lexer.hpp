#ifndef LEXER
#define LEXER

#include <iostream>
#include <fstream>
#include <map>
#include "Tokens.hpp"

class Lexer {
private: 
    char peek = ' ';
    std::ifstream *input;
    std::map<std::string, Word> words;
    void reserve(Word w);
    void readch();
    bool readch(char c);
public:
    static int line;
    Lexer(std::ifstream *inp);
    Token scan();
};

#endif