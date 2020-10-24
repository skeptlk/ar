#include "Lexer.hpp"


int Lexer::line = 1;

Lexer::Lexer(std::ifstream *inp) {
    input = inp;
    reserve( new Word("if",   Tag::IF)  );
    reserve( new Word("then", Tag::THEN));
    reserve( new Word("else", Tag::ELSE));
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
    case ':':
        if (readch('&')) { outp += ":="; return (Token*)&(Word::_asgn); }
        else             { outp += ":"; return new Token((Tag)':'); }
    case '&':
        if (readch('&')) { outp += "&&"; return (Token*)&(Word::_and); }
        else             { outp += "&"; return new Token((Tag)'&'); }
    case '|':
        if (readch('|')) { outp += "||"; return (Token*)&(Word::_or); }
        else             { outp += "|"; return new Token((Tag)'|'); }
    case '=':
        if (readch('=')) { outp += "=="; return (Token*)&(Word::_eq); }
        else             { outp += "="; return new Token((Tag)'='); }
    case '!':
        if (readch('=')) { outp += "!="; return (Token*)&(Word::_ne); }
        else             { outp += "!"; return new Token((Tag)'!'); }
    case '<':
        if (readch('=')) { outp += "<="; return (Token*)&(Word::_le); }
        else             { outp += "<"; return new Token((Tag)'<'); }
    case '>':
        if (readch('=')) { outp += ">="; return (Token*)&(Word::_ge); }
        else             { outp += ">"; return new Token((Tag)'>'); }
    }
    
    if (isdigit(peek)) {
        int v = 0;
        do {
            v = 10*v + (peek - '0');
            readch();
        } while ( isdigit(peek) );
        if (peek != '.') {
            if (words.find(std::to_string(v)) != words.end()) {
                outp += "_" + std::to_string(v) + "_";
                return words[std::to_string(v)];
            }
            Num *n = new Num(v);
            words.insert({std::to_string(v), n});
            outp += "_" + n->toString() + "_";
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
        outp += std::to_string(x);
        if (words.find(std::to_string(v)) != words.end()) {
            outp += "_" + std::to_string(v) + "_";
            return words[std::to_string(v)];
        }
        Real *n = new Real(v);
        words.insert({std::to_string(v), n});
        outp += "_" + n->toString() + "_";
        return n;
    }
    if (isalpha(peek)) {
        std::string s;
        do {
            s += peek; readch();
        } while ( isalnum(peek) );
        if (words.find(s) != words.end()) {
            outp += "_" + words[s]->toString() + "_";
            return words[s];
        }
        Word *w = new Word(s, Tag::ID);
        words.insert({s, w});
        outp += "_" + words[s]->toString() + "_";
        return w;
    }
    // do i need this?
    if (iseof)
        return new Token((Tag)0);

    Token *tok = new Token((Tag)peek); 
    outp += std::string(1, peek);
    peek = ' ';
    return tok;
}

void Lexer::printTable() {
    int i = 1;
    const int len = 20;
    std::string buf;
    buf = "\n---------------------";
    for (int j = 0; j < len; j++)
        buf += "-";
    buf += "\n";
    for (auto pair : words)
    {
        buf += "| " + std::to_string(i) + "\t| " + pair.first;
        i++;
        for (int j = len - pair.first.length(); j > 0; j--) 
            buf += " ";
        buf += "| " + std::to_string((int)pair.second->tag) + "\t|\n";
    }
    buf += "---------------------";
    for (int j = 0; j < len; j++)
        buf += "-";
    buf += "\n";
    std::cout << buf;
}

