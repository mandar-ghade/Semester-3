#include "binary.h"
#include <stdexcept>

void Binary::dbg() {
    throw std::runtime_error("Not implemented yet.");
}
std::string Binary::to_string() {
    throw std::runtime_error("Not implemented yet.");
}
bool Binary::calculate() {
    throw std::runtime_error("Not implemented yet.");
}
void Binary::get_truth_table() {
    throw std::runtime_error("Not implemented yet.");
}

void And::dbg() {
    throw std::runtime_error("Not implemented yet.");
}
std::string And::to_string() {
    throw std::runtime_error("Not implemented yet.");
}
bool And::calculate() {
    return left->calculate() && right->calculate();
}
void And::get_truth_table() {
    throw std::runtime_error("Not implemented yet.");
}


void Or::dbg() {
    throw std::runtime_error("Not implemented yet.");
}
std::string Or::to_string() {
    throw std::runtime_error("Not implemented yet.");
}
bool Or::calculate() {
    return left->calculate() || right->calculate();
}
void Or::get_truth_table() {
    throw std::runtime_error("Not implemented yet.");
}


void Xor::dbg() {
    throw std::runtime_error("Not implemented yet.");
}
std::string Xor::to_string() {
    throw std::runtime_error("Not implemented yet.");
}
bool Xor::calculate() {
    bool l = left->calculate();
    bool r = right->calculate();
    return (l || r) && (l != r);
}
void Xor::get_truth_table() {
    throw std::runtime_error("Not implemented yet.");
}


void IFF::dbg() {
    throw std::runtime_error("Not implemented yet.");
}
std::string IFF::to_string() {
    throw std::runtime_error("Not implemented yet.");
}
bool IFF::calculate() {
    return left->calculate() == right->calculate();
}
void IFF::get_truth_table() {
    throw std::runtime_error("Not implemented yet.");
}


void Implies::dbg() {
    throw std::runtime_error("Not implemented yet.");
}
std::string Implies::to_string() {
    throw std::runtime_error("Not implemented yet.");
}
bool Implies::calculate() {
    return !(left->calculate() && !right->calculate());
}
void Implies::get_truth_table() {
    throw std::runtime_error("Not implemented yet.");
}


