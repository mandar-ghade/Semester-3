#pragma once
#include "operator.h"
#include "symbol.h"
#include <memory>

class Unary: public Operator {
protected:
    Operator& wrapped_expr;
public:
    Unary(Operator& op): wrapped_expr(op) {}
    std::string to_string() override;
    bool calculate() override;
    void dbg() override;
    void get_truth_table() override;
};

class Not: public Unary {
public:
    Not(Operator& op) : Unary(op) {}
    std::string to_string() override;
    bool calculate() override;
    void dbg() override;
    void get_truth_table() override;
};
