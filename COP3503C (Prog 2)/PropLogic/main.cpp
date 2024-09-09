#include "binary.h"
#include "symbol.h"
#include "unary.h"
#include <iostream>
#include <memory>

void print_result(bool res) {
    std::cout << (res ? "true" : "false") << '\n';
}

int main() {
    auto a = std::make_shared<Symbol>("a");
    auto b = std::make_shared<Symbol>("b");
    a->set_truth_value(true);
    b->set_truth_value(true);
    auto implies = std::make_shared<Implies>(a, b);
    print_result(implies->calculate());
    return 0;
}

