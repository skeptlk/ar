#ifndef ENV 
#define ENV 

#include <map>
#include "Inter.hpp"
#include "Tokens.hpp"


class Env {
private:
    std::map<Token*, Id*> *table;
protected: 
    Env *prev;
public:
    Env(Env *n) {
        table = new std::map<Token*, Id*>();
        prev = n;
    }
    void put(Token *w, Id *i) {
        table->insert({ w, i });
    }
    Id * get(Token *w) {
        for (Env *e = this; e != nullptr; e = e->prev)
        {
            if (table->find(w) != table->end())
                return e->table->at(w);
        }
        return nullptr;
    }

};


#endif