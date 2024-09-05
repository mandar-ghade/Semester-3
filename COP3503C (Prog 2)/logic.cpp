#include <iostream>

class Symbol {
    const std::string& str;
public:
    Symbol(const std::string& str): str(str) {}
    const std::string& get_str() {
        return str;
    }
    void dbg() {
        std::cout << str << '\n';
    }
};

int main() {
    Symbol a("a");
    a.dbg();
    return 0;
}

class Operator {
public:
    virtual void dbg() = 0;
    virtual Operator parse(const std::string& input) = 0;
    virtual bool calculate() = 0;
};

class Unary: Operator {
    const Operator& one;
    const Operator& two;
public:
    Unary(const Operator& one, const Operator& two) : one(one), two(two) {}
};

class Binary: Operator {
};

class Neg: Unary {

};

class And: Binary {

};

class Or: Binary {

};

class Xor: Binary {

};

class IFF: Binary {

};

class Implies: Binary {

};
