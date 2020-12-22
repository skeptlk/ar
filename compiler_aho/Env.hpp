#ifndef ENV 
#define ENV 

#include <map>
#include "Inter.hpp"
#include "Tokens.hpp"


class Env {
private:
    // todo: comment changes to original code's hashtable 
    std::map<std::string, Id*> *table;
protected: 
    Env *prev;
public:
    Env(Env *n) {
        table = new std::map<std::string, Id*>();
        prev = n;
    }
    void put(Token *w, Id *i) {
        table->insert({ ((Word*)w)->lexeme, i });
    }
    Id * get(Token *w) {
        std::string word = ((Word*)w)->lexeme;
        for (Env *e = this; e != nullptr; e = e->prev)
        {
            if (e->table->find(word) != e->table->end())
                return e->table->at(word);
        }
        return nullptr;
    }

};


#endif