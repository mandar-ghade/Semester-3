#include "binary.h"
#include "symbol.h"
#include "unary.h"
#include <iostream>
#include <memory>

void calculate_result(std::shared_ptr<Operator> op) {
    std::cout << (op->calculate() ? "true" : "false") << '\n';
}

int main() {
    auto a = std::make_shared<Symbol>("a");
    auto b = std::make_shared<Symbol>("b");
    a->set_truth_value(false);
    b->set_truth_value(true);
    auto xor_op = std::make_shared<Xor>(a, b);
    calculate_result(xor_op);
    return 0;
}

