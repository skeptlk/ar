#ifndef TOKENS
#define TOKENS

#include "Tag.hpp"
#include <iostream>

class Token {
public:
    Tag tag;
    Token();
    Token(Tag t);
    std::string toString();
};


class Num : public Token {
public: 
    int value;
    Num(int v);
    std::string toString();
};

class Real : public Token {
public: 
    float value;
    Real(float v);
    std::string toString();
};


class Word: public Token {
public: 
    std::string lexeme = "";
    Word();
    Word(std::string s, Tag tag);
    static Word 
        _and, _or, _eq, _ne, _le, _ge, _asgn, 
        _minus, _true, _false, _temp;
};


class Type: public Word {
public:
    int width = 0;  // width is used for storage allocation
    Type();         // default construtor
    Type(std::string s, Tag tag, int w);

    static Type _int, _float, _char, _bool, _null;
    static bool numeric(Type p);
    static Type max(Type p1, Type p2);
};

class Array: public Type {
public:
    Type of;
    int size = 1;
    Array(int sz, Type p);
    std::string toString();
};


#endif