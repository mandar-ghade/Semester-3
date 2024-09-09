#pragma once
#include <array>
#include <iostream>
#include <memory>
#include <vector>

class Operator {
protected:
    static std::shared_ptr<Operator> convert_to_shared_ptr(Operator& ref); 
public:
    virtual ~Operator() = default;
    virtual void dbg() = 0;
    static Operator& parse(const std::string&); 
    virtual std::string to_string() = 0;
    virtual bool calculate() = 0;
    virtual void get_truth_table() = 0;
    //virtual std::vector<std::vector<bool>> truth_table_as_list() = 0;
};
