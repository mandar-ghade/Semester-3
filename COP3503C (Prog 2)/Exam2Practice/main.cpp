#include <iostream>
#include <fstream>
#include <cstring>

class Mult {
	int operator()(int lhs, int rhs) {
		return lhs + rhs;
	}
};

int add(int one, int two) {
	return one + two;
}

int subtract(int one, int two) {
	return one - two;
}

int multiply(int one, int two) {
	return one * two;
}

int run_func(int (*funct)(int, int), int lhs, int rhs) {
	return funct(lhs, rhs);
}


int main() {
	std::cout << "Input add, subtract, or multiply: \n";
	std::string input;
	std::cin >> input;
	int num;
	std::cout << "Ok, now input a number:\n";
	std::cin >> num;
	int (*func)(int, int) = nullptr;
	if (input == "add") {
		func = add;
	} else if (input == "subtract") {
		func = subtract;
	} else if (input == "multiply") {
		func = multiply;
	}
	if (func) {
		std::cout << run_func(func, num, num) << '\n';
	}
	return 0;
}
