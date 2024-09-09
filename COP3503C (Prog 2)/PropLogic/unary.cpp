#include "unary.h"
#include <stdexcept>
std::string Unary::to_string() {
    throw std::runtime_error("Unary: to_string should've been defined");
}
bool Unary::calculate() {
    throw std::runtime_error("Unary: Calculate should've been defined");
}
void Unary::dbg() {
    return;
}
void Unary::get_truth_table() {
    return;
}

std::string Not::to_string() {
    return "";
}

void Not::dbg() {
    return;
}

void Not::get_truth_table() {
    return;
}

bool Not::calculate() {
    return !wrapped_expr->calculate();
}
