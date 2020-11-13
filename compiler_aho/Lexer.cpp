#include "Lexer.hpp"

int Lexer::line = 1;

Lexer::Lexer(std::ifstream *inp) {
    input = inp;
    reserve( new Word("if",    Tag::IF)    );
    reserve( new Word("else",  Tag::ELSE)  );
    reserve( new Word("while", Tag::WHILE) );
    reserve( new Word("do",    Tag::DO)    );
    reserve( new Word("break", Tag::BREAK) );
    reserve( &Word::_true );  reserve( &Word::_false );
    reserve( &Type::_int  );  reserve( &Type::_char  );
    reserve( &Type::_bool );  reserve( &Type::_float );
}

void Lexer::reserve (Word *w) { 
    words.insert({ w->lexeme, w });
}

void Lexer::readch() { 
    char temp;
    if (!input->get(temp))
        iseof = true;
    else peek = temp;
} 

bool Lexer::readch(char c) {
    readch();
    if (peek != c) return false;
    peek = ' ';
    return true;
}

Token* Lexer::scan() {
    for ( ; !iseof; readch() ) {
        if (peek == ' ' || peek == '\t') continue;
        else if (peek == '\n') line = line + 1;
        else break;
    }

    switch (peek)
    {
    case '&':
        if (readch('&')) return (Token*)&(Word::_and);
        else             return new Token((Tag)'&');
    case '|':
        if (readch('|')) return (Token*)&(Word::_or);
        else             return new Token((Tag)'|');
    case '=':
        if (readch('=')) return (Token*)&(Word::_eq);
        else             return new Token((Tag)'=');
    case '!':
        if (readch('=')) return (Token*)&(Word::_ne);
        else             return new Token((Tag)'!');
    case '<':
        if (readch('=')) return (Token*)&(Word::_le);
        else             return new Token((Tag)'<');
    case '>':
        if (readch('=')) return (Token*)&(Word::_ge);
        else             return new Token((Tag)'>');
    }
    
    if (isdigit(peek)) {
        int v = 0;
        do {
            v = 10*v + (peek - '0');
            readch();
        } while ( isdigit(peek) );
        if (peek != '.') 
            return new Num(v);
        float x = v;
        float d = 10;
        for (;;) {
            readch();
            if (!isdigit(peek)) break;
            x = x + (peek - '0') / d; 
            d = d * 10;
        }
        return new Real(x);
        if (isalpha(peek)) {
            std::string s;
            do {
                s += peek; readch();
            } while ( isalnum(peek) );
            if (words.find(s) != words.end());
                return (words[s]);
            Token *w = new Word(s, Tag::ID);
            words.insert({s, w});
            return w;
        }
        // do i need this?
        if (iseof)
            return new Token((Tag)0);

        Token *tok = new Token((Tag)peek); 
        peek = ' ';
        return tok;
    }
}

