#include <fstream>
#include <iostream>

template<typename T>
class ABS {
	const size_t scale_factor = 2;
	size_t size = 0; 
	size_t capacity = 1;
	T** data;
private:
	void free() {
		if (size != 0) {
			for (size_t i = 0; i < size; i++) {
				delete data[i];
			}
		}
		delete[] data;
	}
	T** array_with_size(const size_t new_size) const {
		return new T*[new_size];
	}
	void overwrite_array(T** target, T** old, size_t old_size) const {
		for (size_t i = 0; i < old_size; i++) {
			target[i] = old[i];
		}
	}
	void resize_array(const size_t new_capacity) {
		T** new_data = array_with_size(new_capacity);
		overwrite_array(new_data, data, size);
		delete[] data; // so we keep the pointers, but not the array
		data = new_data;
		capacity = new_capacity;
	}
public:
	ABS (): data(array_with_size(capacity)) {};
	ABS (int cap) {
		data = array_with_size(cap); 
		capacity = cap;
	}
	ABS (const ABS &other) {
		data = array_with_size(other.capacity);
		overwrite_array(data, other.data, other.size);
		size, capacity = other.size, other.capacity;
	}
	ABS& operator=(const ABS &rhs) { // no heap?
		free(); // deletes pre existing data
		data = array_with_size(rhs.capacity);
		overwrite_array(data, rhs.data, rhs.size);
		size, capacity = rhs.size, rhs.capacity;
		return this;
	}
	~ABS() {
		free();
	}
	void push(T t) {
		if (size == capacity) {
			resize_array(size * scale_factor);
		}
		data[size++] = new T(t);
	}
	T* getData() const {
		return data;
	}
	T pop() {
		if (size == 0) {
			throw std::runtime_error("Nothing to pop (stack is empty)");
		}
		T top = *data[--size];
		delete data[size];
		if (
			(static_cast<double>(size) / static_cast<double>(capacity)) < 
			(1 / static_cast<double>(scale_factor))
		) {
			resize_array(static_cast<size_t>(static_cast<double>(capacity) / static_cast<double>(scale_factor)));
		}
		return top;
	}
	T peek() const {
		if (size == 0) {
			throw std::runtime_error("Nothing to peek (stack is empty)");
		}
		return *data[size - 1];
	}
	unsigned int getSize() const {
		return size;
	}
	unsigned int getMaxCapacity() const {
		return capacity;
	}
};

