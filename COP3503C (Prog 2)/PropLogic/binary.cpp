#include "binary.h"
#include <stdexcept>

std::string bool_to_str(bool b) {
    return b ? "true" : "false";
}

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
    std::cout << to_string() << '\n';
}
std::string And::to_string() {
    return "And {" + left.to_string() + ", " + right.to_string() + "} = " + bool_to_str(calculate());
}
bool And::calculate() {
    return left.calculate() && right.calculate();
}
void And::get_truth_table() {
    throw std::runtime_error("Not implemented yet.");
}


void Or::dbg() {
    std::cout << to_string() << '\n';
}
std::string Or::to_string() {
    return "Or {" + left.to_string() + ", " + right.to_string() + "} = " + bool_to_str(calculate());
}
bool Or::calculate() {
    return left.calculate() || right.calculate();
}
void Or::get_truth_table() {
    throw std::runtime_error("Not implemented yet.");
}


void Xor::dbg() {
    std::cout << to_string() << '\n';
}
std::string Xor::to_string() {
    return "Xor {" + left.to_string() + ", " + right.to_string() + "} = " + bool_to_str(calculate());
}
bool Xor::calculate() {
    bool l = left.calculate();
    bool r = right.calculate();
    return (l || r) && (l != r);
}
void Xor::get_truth_table() {
    throw std::runtime_error("Not implemented yet.");
}


void IFF::dbg() {
    std::cout << to_string() << '\n';
}
std::string IFF::to_string() {
    return "IFF {" + left.to_string() + ", " + right.to_string() + "} = " + bool_to_str(calculate());
}
bool IFF::calculate() {
    return left.calculate() == right.calculate();
}
void IFF::get_truth_table() {
    throw std::runtime_error("Not implemented yet.");
}

void Implies::dbg() {
    std::cout << to_string() << '\n';
}
std::string Implies::to_string() {
    return "Implies {" + left.to_string() + ", " + right.to_string() + "} = " + bool_to_str(calculate());
}
bool Implies::calculate() {
    return (!left.calculate() || right.calculate());
}
void Implies::get_truth_table() {
    throw std::runtime_error("Not implemented yet.");
}


