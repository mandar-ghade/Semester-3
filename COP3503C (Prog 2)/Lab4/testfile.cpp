#include <iostream>
#include "ABS.h"
#include "ABQ.h"

void test_abs() {
	ABS<int> new_abs(2);
	int integ = 5;
	new_abs.push(integ);
	new_abs.push(integ);
	new_abs.push(integ);
	new_abs.push(integ);
	new_abs.push(7);
	new_abs.push(8);
	std::cout << new_abs.pop() << '\n';
	std::cout << new_abs.pop() << '\n';
	std::cout << new_abs.pop() << '\n';
	std::cout << new_abs.pop() << '\n';
	std::cout << new_abs.pop() << '\n';
	std::cout << new_abs.pop() << '\n';
	new_abs.push(8);
	std::cout << new_abs.peek() << '\n';
	std::cout << new_abs.getSize() << '\n';
	std::cout << new_abs.getMaxCapacity() << '\n';
}

void test_abq() {
	ABQ<int> new_abq(2);
	new_abq.enqueue(5);
	new_abq.enqueue(6);
	new_abq.enqueue(7);
	new_abq.enqueue(8);
	std::cout << new_abq.dequeue() << '\n';
	std::cout << new_abq.dequeue() << '\n';
	std::cout << new_abq.dequeue() << '\n';
	new_abq.enqueue(9);
	std::cout << new_abq.dequeue() << '\n';
	std::cout << new_abq.dequeue() << '\n';
	new_abq.enqueue(10);

	ABQ<int> new_abq_2(new_abq);

	std::cout << new_abq_2.getSize() << '\n';
	std::cout << new_abq.getSize() << '\n';
	std::cout << new_abq.getMaxCapacity() << '\n';
}

int main() {
	test_abq();
	return 0;
	
}
