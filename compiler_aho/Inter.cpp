#include "Inter.hpp"


/**
 *      OP
 */

Op::Op(Token tok, Type p):Expr(tok, p) 
{}

Expr* Op::reduce()


