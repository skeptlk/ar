#include "Env.hpp"

Env::Env(Env *n)
{
    table = new std::map<Token*, Id*>();
    prev = n;
}

void Env::put(Token *w, Id *i)
{
    table->insert({ w, i });
}

Id* Env::get(Token *w)
{
    for (Env *e = this; e != nullptr; e = e->prev)
    {
        if (table->find(w) != table->end())
            return e->table->at(w);
        return nullptr;
    }
}
