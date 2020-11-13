#include "Lexer.hpp"

int Lexer::line = 1;

Lexer::Lexer(std::ifstream *inp) {
    input = inp;
    words = new Hashtable();
    reserve( new Word("if",    Tag::IF)    );
    reserve( new Word("else",  Tag::ELSE)  );
    reserve( new Word("then",  Tag::THEN)  );
    reserve( new Word("while", Tag::WHILE) );
    reserve( new Word("do",    Tag::DO)    );
    reserve( new Word("break", Tag::BREAK) );
    reserve( &Word::_true );  reserve( &Word::_false );
    reserve( &Type::_int  );  reserve( &Type::_char  );
    reserve( &Type::_bool );  reserve( &Type::_float );
}

void Lexer::reserve (Word *w) { 
    words->insert(w->lexeme, w);
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
    case ':':
        if (readch('=')) return &Word::_asgn;
        else             return new Token((Tag)':');
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
        if (peek != '.') {
            Token *n;
            if (n = words->find(std::to_string(v)))
                return n;
            n = new Num(v);
            words->insert(std::to_string(v), n);
            return n;
        }
        float x = v;
        float d = 10;
        for (;;) {
            readch();
            if (!isdigit(peek)) break;
            x = x + (peek - '0') / d; 
            d = d * 10;
        }
        Token *r;
        if (r = words->find(std::to_string(x)))
            return r;
        r = new Real(x);
        words->insert(std::to_string(x), r);
        return r;
    }
    if (isalpha(peek)) {
        std::string s;
        do {
            s += peek; readch();
        } while ( isalnum(peek) );
        Token *w;
        if (w = words->find(s))
            return w;
        w = new Word(s, Tag::ID);
        words->insert(s, w);
        return w;
    }
    // do i need this?
    if (iseof)
        return new Token((Tag)0);

    Token *tok = new Token((Tag)peek); 
    peek = ' ';
    return tok;
}

void Lexer::printTable() {
    words->print();
}

