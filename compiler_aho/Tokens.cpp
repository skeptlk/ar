#include "Tokens.hpp"


/**
 *          ARRAY
 */

Array::Array(int sz, Type p)
    :Type("[]", Tag::INDEX, sz*p.width) 
{
    size = sz;
    of = p;
}

std::string Array::toString()
{
    return "[" + std::to_string(size) + "]" + of.toString();
}
