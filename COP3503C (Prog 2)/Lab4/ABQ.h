#include <iostream>
#include <stdexcept>

template<typename T>
class ABQ {
	const size_t scale_factor = 2;
	size_t size = 0; // size of array, not how much data is stored.
	size_t capacity = 1;
	size_t offset = 0; // next in queue, start idx
	T** data;
private:
	void free() {
		// starts at offset - no more double mem dealloc error
		for (size_t i = offset; i < size; i++) {
			delete data[i];
		}
		delete[] data;
	}
	T** array_with_size(const size_t new_size) const {
		return new T*[new_size];
	}
	void overwrite_array(
		T** target, 
		T** old,
		size_t old_size,
		size_t old_offset
	) const {
		// old: [old_offset, old_size]
		// total size = old_size - old_offset
		// target: [0, old_size - old_offset]
		//if (start > 0) start -= 1; // because we increment offset every time we dequeue
		for (size_t i = old_offset; i < old_size; i++) {
			target[i - old_offset] = old[i]; 
		}
	}
	void resize_array(const size_t new_capacity) {
		T** new_data = array_with_size(new_capacity);
		overwrite_array(new_data, data, size, offset);
		size -= offset; // nice fix
		offset = 0; // reset offset
		delete[] data; // we keep the pointers, but not the array
		data = new_data;
		capacity = new_capacity;
	}
public:
	ABQ (): data(array_with_size(capacity)) {};
	ABQ (int cap) {
		data = array_with_size(cap); 
		capacity = cap;
	}
	ABQ (const ABQ &other) {
		// consider making fresh copies
		data = array_with_size(other.capacity);
		overwrite_array(data, other.data, other.size, other.offset);
		size = other.size;
		capacity = other.capacity; // offset = 0 automatic
	}
	ABQ &operator=(const ABQ &rhs) { 
		free();
		data = array_with_size(rhs.capacity);
		overwrite_array(data, rhs.data, rhs.size, rhs.offset);
		size = rhs.size;
		capacity = rhs.capacity;
		offset = 0;
		return this;
	}
	~ABQ() {
		free();
	}
	void enqueue(T t) {
		if (size == capacity) {
			resize_array(capacity * scale_factor);
		}
		//std::cout << "New size: " << size << " Cap: " << capacity << '\n';
		data[size++] = new T(t);
	}
	T* getData() const {
		return data;
	}
	T dequeue() {
		if (size - offset == 0) { // represents current size
			throw std::runtime_error("Queue not dequeable (queue is empty)");
		}
		// std::cout << "Attempting dequeue at: " << offset << " size: " << size << " cap: " << capacity << '\n';
		T last = *data[offset];
		delete data[offset++];
		if (
			(static_cast<double>(size - offset) / static_cast<double>(capacity))
			< (1 / static_cast<double>(scale_factor))
		) {
			resize_array(static_cast<size_t>(
				static_cast<double>(capacity) / static_cast<double>(scale_factor))
			);
		}
		return last;
	}
	T peek() const {
		if (size - offset == 0) { // represents current size
			throw std::runtime_error("Queue not peekable (queue is empty)");
		}
		return *data[offset];
	}
	unsigned int getSize() const {
		return size - offset;
	}
	unsigned int getMaxCapacity() const {
		return capacity;
	}
};

