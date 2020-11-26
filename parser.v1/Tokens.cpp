#include "Tokens.hpp"

/**
 *          TOKEN
 */

Token::Token() {};

Token::Token(Tag t) {
    tag = t;
}

std::string Token::toString() {
    std::string s(1, (char) tag);
    return s;
}


/**
 *          NUM
 */

Num::Num(int v): Token(Tag::NUM) {
    value = v;
}

std::string Num::toString() {
    return std::to_string(value);
}


/**
 *          REAL
 */

Real::Real(float v): Token(Tag::REAL) {
    value = v;
}

std::string Real::toString() {
    return std::to_string(value);
}


/**
 *          WORD
 */

// default constructor for map
Word::Word(): Token((Tag)0) {};



std::string Word::toString() {
    return lexeme;
}

Word Word::_and   = Word("&&", Tag::AND); 
Word Word::_or    = Word("||", Tag::OR); 
Word Word::_eq    = Word("==", Tag::EQ); 
Word Word::_ne    = Word("!=", Tag::NE); 
Word Word::_le    = Word("<=", Tag::LE); 
Word Word::_ge    = Word(">=", Tag::GE); 
Word Word::_asgn  = Word(":=", Tag::ASGN); 
Word Word::_minus = Word("minus", Tag::MINUS); 
Word Word::_true  = Word("true", Tag::TRUE); 
Word Word::_false = Word("false", Tag::FALSE); 
Word Word::_temp  = Word("temp", Tag::TEMP); 

/**
 *          TYPE
 */

Type::Type() {};

Type::Type(std::string s, Tag tag, int w): Word(s, tag) { 
    width = w; 
}

bool Type::numeric(Type p) {
    return (p.lexeme == Type::_char.lexeme ||
        p.lexeme == Type::_int.lexeme ||
        p.lexeme == Type::_float.lexeme);
}

Type Type::max(Type p1, Type p2) {
    if ( !numeric(p1) || !numeric(p2) ) return Type::_null;
    else if (p1.lexeme == "float" || p2.lexeme == "float") return Type::_float;
    else if (p1.lexeme == "int" || p2.lexeme == "int") return Type::_int;
    else return Type::_char;
}

Type Type::_int   = Type("int",   Tag::BASIC, 4);
Type Type::_float = Type("float", Tag::BASIC, 8);
Type Type::_char  = Type("char",  Tag::BASIC, 1);
Type Type::_bool  = Type("bool",  Tag::BASIC, 1);
Type Type::_null  = Type("null",  (Tag) 0, 0); // we need this to return null from max


/**
 *          ARRAY
 */

Array::Array(int sz, Type p): Type("[]", Tag::INDEX, sz*p.width) {
    size = sz;
    of = p;
}

std::string Array::toString()
{
    return "[" + std::to_string(size) + "]" + of.toString();
}
