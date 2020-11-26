#ifndef TOKENS
#define TOKENS

#include "Tag.hpp"
#include <iostream>

class Token {
public:
    Tag tag;
    Token() {};
    Token(Tag t) { tag = t; }
    virtual std::string toString() {
        return std::to_string((int) tag);
    }
};


class Num : public Token {
public: 
    int value;
    Num(int v): Token(Tag::NUM) {
        value = v;
    }
    std::string toString() {
        return std::to_string(value);
    }
};

class Real : public Token {
public: 
    float value;
    Real(float v): Token(Tag::REAL) {
        value = v;
    }
    std::string toString() {
        return std::to_string(value);
    }
};


class Word: public Token {
public: 
    std::string lexeme = "";
    Word(): Token((Tag)0) {};
    Word(std::string s, Tag tag): Token(tag) {
        lexeme = s;
    }
    static Word 
        _and, _or, _eq, _ne, _le, _ge, 
        _minus, _true, _false, _temp;
};

Word Word::_and   = Word("&&", Tag::AND); 
Word Word::_or    = Word("||", Tag::OR); 
Word Word::_eq    = Word("==", Tag::EQ); 
Word Word::_ne    = Word("!=", Tag::NE); 
Word Word::_le    = Word("<=", Tag::LE); 
Word Word::_ge    = Word(">=", Tag::GE); 
Word Word::_minus = Word("minus", Tag::MINUS); 
Word Word::_true  = Word("true", Tag::TRUE); 
Word Word::_false = Word("false", Tag::FALSE); 
Word Word::_temp  = Word("temp", Tag::TEMP); 


class Type: public Word {
public:
    int width = 0;  // width is used for storage allocation
    Type() {}
    Type(std::string s, Tag tag, int w): Word(s, tag) { 
        width = w; 
    }
    static Type _int, _float, _char, _bool;
    static bool numeric(Type * p) {
        return (p->lexeme == Type::_char.lexeme ||
            p->lexeme == Type::_int.lexeme ||
            p->lexeme == Type::_float.lexeme);
    }
    static Type * max(Type *p1, Type *p2) {
        if ( !numeric(p1) || !numeric(p2) ) return nullptr;
        else if (p1->lexeme == "float" || p2->lexeme == "float") return &Type::_float;
        else if (p1->lexeme == "int" || p2->lexeme == "int") return &Type::_int;
        else return &Type::_char;
    }
};

Type Type::_int   = Type("int",   Tag::BASIC, 4);
Type Type::_float = Type("float", Tag::BASIC, 8);
Type Type::_char  = Type("char",  Tag::BASIC, 1);
Type Type::_bool  = Type("bool",  Tag::BASIC, 1);


class Array: public Type {
public:
    Type of;
    int size = 1;
    Array(int sz, Type p)
        :Type("[]", Tag::INDEX, sz*p.width) {
        size = sz;
        of = p;
    }
    std::string toString() {
        return "[" + std::to_string(size) + "]" + of.toString();
    }
};


#endif