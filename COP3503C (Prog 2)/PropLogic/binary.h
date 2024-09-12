#pragma once
#include "operator.h"
#include "symbol.h"
#include <memory>
#include <vector>

std::string bool_to_str(bool b); 

class Binary: public Operator {
protected:
    Operator& left;
    Operator& right;
public:
    Binary(
        Operator& left,
        Operator& right
    ): left(left), right(right) {}
    void dbg() override;
    std::string to_string() override;
    bool calculate() override;
    void get_truth_table() override;
};

class And: public Binary {
public:
    And(
        Operator& left,
        Operator& right
    ): Binary(left, right) {}
    void dbg() override;
    std::string to_string() override;
    bool calculate() override;
    void get_truth_table() override;
};

class Or: public Binary {
public:
    Or(
        Operator& left,
        Operator& right
    ): Binary(left, right) {}
    void dbg() override;
    std::string to_string() override;
    bool calculate() override;
    void get_truth_table() override;
};

class Xor: public Binary {
public:
    Xor(
        Operator& left,
        Operator& right
    ): Binary(left, right) {}
    void dbg() override;
    std::string to_string() override;
    bool calculate() override;
    void get_truth_table() override;
};

class IFF: public Binary {
public:
    IFF(
        Operator& left,
        Operator& right
    ): Binary(left, right) {}
    void dbg() override;
    std::string to_string() override;
    bool calculate() override;
    void get_truth_table() override;
};

class Implies: public Binary {
public:
    Implies(
        Operator& left,
        Operator& right
    ): Binary(left, right) {}
    void dbg() override;
    std::string to_string() override;
    bool calculate() override;
    void get_truth_table() override;
};

