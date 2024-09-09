#include <iostream>
#include "symbol.h"

std::string Symbol::to_string() {
    return this->str;
}

void Symbol::dbg() {
    std::cout << str << '\n';
}

void Symbol::set_truth_value(bool value) {
    this->truth_value = value;
}

bool Symbol::get_truth_value() {
    return this->truth_value;
}

bool Symbol::calculate() {
    return this->truth_value;
}

void Symbol::get_truth_table() {
    throw std::runtime_error("Symbol: Get truth table should've been defined");
}
