#ifndef ENV 
#define ENV 

#include <map>
#include "Tokens.hpp"


class Id{};

class Env {
private:
    std::map<Token, Id> *table;
protected: 
    Env *prev;
public:
    Env(Env *n);
    void put(Token w, Id i);
    Id get(Token w);
};

Env::Env(Env *n)
{
    table = new std::map<Token, Id>();
    prev = n;
}

void Env::put(Token w, Id i)
{
    table->insert({ w, i });
}

Id Env::get(Token w)
{
    for (Env *e = this; e != nullptr; e = e->prev)
    {
        if (table->find(w) != table->end())
            return e->table->at(w);
        // return nullptr;
    }
}


#endif