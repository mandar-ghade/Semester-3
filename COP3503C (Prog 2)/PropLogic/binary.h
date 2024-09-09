#pragma once
#include "operator.h"
#include "symbol.h"
#include <memory>
#include <vector>

class Binary: public Operator {
protected:
    std::shared_ptr<Operator> left;
    std::shared_ptr<Operator> right;
public:
    Binary(
        std::shared_ptr<Operator> left,
        std::shared_ptr<Operator> right
    ): left(left), right(right) {}
    void dbg() override;
    std::string to_string() override;
    bool calculate() override;
    void get_truth_table() override;
};

class And: public Binary {
public:
    And(
        std::shared_ptr<Operator> left,
        std::shared_ptr<Operator> right
    ): Binary(left, right) {}
    void dbg() override;
    std::string to_string() override;
    bool calculate() override;
    void get_truth_table() override;
};

class Or: public Binary {
public:
    Or(
        std::shared_ptr<Operator> left,
        std::shared_ptr<Operator> right
    ): Binary(left, right) {}
    void dbg() override;
    std::string to_string() override;
    bool calculate() override;
    void get_truth_table() override;
};

class Xor: public Binary {
public:
    Xor(
        std::shared_ptr<Operator> left,
        std::shared_ptr<Operator> right
    ): Binary(left, right) {}
    void dbg() override;
    std::string to_string() override;
    bool calculate() override;
    void get_truth_table() override;
};

class IFF: public Binary {
public:
    IFF(
        std::shared_ptr<Operator> left,
        std::shared_ptr<Operator> right
    ): Binary(left, right) {}
    void dbg() override;
    std::string to_string() override;
    bool calculate() override;
    void get_truth_table() override;
};

class Implies: public Binary {
public:
    Implies(
        std::shared_ptr<Operator> left,
        std::shared_ptr<Operator> right
    ): Binary(left, right) {}
    void dbg() override;
    std::string to_string() override;
    bool calculate() override;
    void get_truth_table() override;
};

