#include "binary.h"
#include "operator.h"
#include "symbol.h"
#include "unary.h"
#include <iostream>
#include <memory>

int main() {
    Symbol a("a", true);
    Symbol b("b", true);
    Xor xor_op = Xor(a, b);
    Not neg_op = Not(xor_op);
    neg_op.dbg();
    return 0;
}

