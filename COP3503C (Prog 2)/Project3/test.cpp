#include <iostream>
#include <map>

int test() {
	std::map<int, int> m;
	m.at(5);
}

int main() {
	test();
	return 0;
}
