#ifndef ENV 
#define ENV 

#include <map>
#include "Tokens.hpp"


class Env {
private:
    std::map<Token*, Id*> *table;
protected: 
    Env *prev;
public:
    Env(Env *n);
    void put(Token *w, Id *i);
    Id* get(Token *w);
};


#endif