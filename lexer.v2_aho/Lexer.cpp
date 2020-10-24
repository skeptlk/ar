#include "Lexer.hpp"

int Lexer::line = 1;

Lexer::Lexer(std::ifstream *inp) {
    input = inp;
    reserve( Word("if",    Tag::IF)    );
    reserve( Word("else",  Tag::ELSE)  );
    reserve( Word("while", Tag::WHILE) );
    reserve( Word("do",    Tag::DO)    );
    reserve( Word("break", Tag::BREAK) );
    reserve( Word::_true );  reserve( Word::_false );
    reserve( Type::_int  );  reserve( Type::_char  );
    reserve( Type::_bool );  reserve( Type::_float );
}

void Lexer::reserve (Word w) { 
    words.insert({ w.lexeme, w });
}

void Lexer::readch() { 
    input->get(peek);
} 

bool Lexer::readch(char c) {
    readch();
    if (peek != c) return false;
    peek = ' ';
    return true;
}

Token Lexer::scan() {
    for ( ; ; readch() ) {
        if (peek == ' ' || peek == '\t') continue;
        else if (peek == '\n') line = line + 1;
        else break;
    }

    switch (peek)
    {
    case '&':
        if (readch('&')) return Word::_and;
        else             return Token((Tag)'&');
    case '|':
        if (readch('|')) return Word::_or;
        else             return Token((Tag)'|');
    case '=':
        if (readch('=')) return Word::_eq;
        else             return Token((Tag)'=');
    case '!':
        if (readch('=')) return Word::_ne;
        else             return Token((Tag)'!');
    case '<':
        if (readch('=')) return Word::_le;
        else             return Token((Tag)'<');
    case '>':
        if (readch('=')) return Word::_ge;
        else             return Token((Tag)'>');
    }
    
    if (isdigit(peek)) {
        int v = 0;
        do {
            v = 10*v + (peek - '0');
            readch();
        } while ( isdigit(peek) );
        if (peek != '.') 
            return Num(v);
        float x = v;
        float d = 10;
        for (;;) {
            readch();
            if (!isdigit(peek)) break;
            x = x + (peek - '0') / d; 
            d = d * 10;
        }
        return Real(x);
        if (isalpha(peek)) {
            std::string s;
            do {
                s += peek; readch();
            } while ( isalnum(peek) );
            if (words.find(s) != words.end());
                return (words[s]);
            Word w(s, Tag::ID);
            words.insert({s, w});
            return w;
        }
        Token tok((Tag)peek); 
        peek = ' ';
        return tok;
    }
}

