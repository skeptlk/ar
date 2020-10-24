#ifndef HASHTABLE
#define HASHTABLE
#include <string>
#include "Tokens.hpp"
#include "Tag.hpp"


/**
 *       OPEN ADDRESSING HASH TABLE
 *       WITH QUADRATIC PROBING
 */

struct Pair {
    bool is_del = false;
    std::string key;
    Token * value;
    Pair(std::string k, Token *val) {
        key = k;
        value = val;
    }
};


class Hashtable {
private: 
    int size;
    Pair** arr;
public:
    int hash(std::string key);
    Hashtable();
    Hashtable(int sz);
    Token* find(std::string key);
    void   insert(std::string key, Token* value);
    void   remove(std::string key);
    void   print();
};



#endif // HASHTABLE