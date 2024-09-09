#pragma once
#include "operator.h"
#include <iostream>

class Symbol: public Operator {
private:
    const std::string& str;
    bool truth_value = false;
public:
    Symbol(const std::string& str): str(str) {}
    Symbol(const std::string& str, bool truth_value): str(str), truth_value(truth_value) {}
    std::string to_string() override;
    void set_truth_value(bool value);
    bool get_truth_value();
    bool operator == (const Symbol &s) {
        return str == s.str;
    }
    void dbg() override;
    bool calculate() override;
    void get_truth_table() override;
};

