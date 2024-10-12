#pragma once
#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class LinkedList {
public:
	struct Node { // why is this public
		T data; // non-const, because of subscript operator shit func
		Node* next = nullptr;
		Node* prev = nullptr; 
		Node(const Node& other): data(other.data) {}
		Node(const T& input_data): data(input_data) {}
		bool operator==(const Node& node) {
			return data == node.data;
		}
		static Node* deep_copy_from(Node* node, Node* prev) {
			Node* head = new Node(node->data);
			if (node->next) {
				head->next = deep_copy_from(node->next, node);
			}
			head->prev = prev;
			return head;
		}
		static Node* get_tail(Node* head) {
			Node* curr = head;
			while (curr->has_next()) {
				curr = curr->next;
			}
			if (curr == head) {
				return nullptr; // there's no tail.
			}
			return curr;
		}
		bool has_next() const {
			return next != nullptr;
		}
		bool has_prev() const {
			return prev != nullptr;
		}
		void free_next_recursive() {
			if (next == nullptr) {
				return;
			}
			if (next->has_next()) {
				next->free_next_recursive();
			}
			delete next;
			next = nullptr;
			prev = nullptr;
		}
	};
	Node* head = nullptr;
	Node* tail = nullptr;
	// Construction / Destruction
	LinkedList() {}
	LinkedList(const LinkedList<T>& list) {
		if (list.head) {
			head = Node::deep_copy_from(list.head, nullptr);
			tail = Node::get_tail(head);
		}
	}
	~LinkedList() {
		if (head) {
			head->free_next_recursive();
			delete head;
		}
		tail = nullptr;
		// tail deletes on its own
	}
	// Insertion
	void AddHead(const T& data) {
		Node* new_head = new Node(data);
		if (head) {
			new_head->next = head;
			head->prev = new_head;
		} else if (!head && !tail) { // edge case
			tail = new_head;
		}
		head = new_head;
	}
	void AddTail(const T& data) {
		Node* new_tail = new Node(data);
		if (tail) {
			tail->next = new_tail;
			new_tail->prev = tail;
		} else if (!tail && !head) {
			head = new_tail;
		}
		tail = new_tail;
	}
	void AddNodesHead(const T* data, unsigned int count) {
		for (int i = count - 1; i >= 0; i--) {
			AddHead(data[i]);
		}
	}
	void AddNodesTail(const T* data, unsigned int count) {
		for (int i = 0; i < count; i++) {
			AddTail(data[i]);
		}
	}
	void InsertAfter(Node* node, const T& data) {
		Node* new_node = new Node(data);
		new_node->next = node->next;
		new_node->prev = node;
		node->next = new_node;
	}
	void InsertBefore(Node* node, const T& data) {
		Node* new_node = new Node(data);
		new_node->next = node;
		new_node->prev = node->prev;
		node->prev->next = new_node;
		node->prev = new_node;
	}
	void InsertAt(const T& data, unsigned int index) {
		if (index < 0) {
			throw std::out_of_range("Out of bounds.");
		} else if (index == 0) {
			AddHead(data);
			return;
		}
		Node* node_before = GetNode(index - 1);
		if (!node_before) {
			throw std::out_of_range("Could not locate node previous to index. Out of range.");
		}
		Node* insertion_node = new Node(data);
		Node* node_after = nullptr; // old "next" pointer
		if (node_before->has_next()) {
			node_after = node_before->next;
			node_after->prev = insertion_node;
		} 
		node_before->next = insertion_node;
		insertion_node->next = node_after;
		insertion_node->prev = node_before;
		if (
			(!tail && !node_after) || node_before == tail) // if no tail ever assigned or if tail is the last node
		{  // tail case
			tail = insertion_node;
		}
	}
	// Removal
	bool RemoveHead() {
		if (head == nullptr) {
			if (tail) tail = nullptr;
			return false;
		}
		Node* next_node = nullptr;
		if (head->has_next()) {
			next_node = head->next;
			next_node->prev = nullptr;
		}
		delete head;
		head = next_node;
		return true;
	}
	bool RemoveTail() {
		if (!head) {
			throw std::runtime_error("Empty LinkedList. Could not remove tail.");
		}
		else if (!head->has_next()) { // edge case
			delete head;
			head = nullptr;
			return false;
		}
		if (tail == nullptr) {
			return false;
		}
		Node* next = head;
		while (next->has_next()) {
			next = next->next;
		}
		if (next != tail && tail != nullptr) {  // checks memory address
			// double checks that tail isn't null for this test to fail.
			throw std::runtime_error("Could not identify position of tail.");
		}
		next->prev->next = nullptr;
		tail = next->prev;
		delete next;
		return true;
	}
	unsigned int Remove(const T& data) {
		if (!head) {
			return 0;
		}
		std::vector<size_t> indices;
		size_t i = 0;
		// second thoughts.. maybe just use while loop
		for (Node* curr = head; curr != nullptr; curr = curr->next) {
			if (curr->data == data) {
				indices.push_back(i);
			}
			i++;
		}
		size_t popped_count = 0;
		for (size_t idx: indices) {
			if (idx - popped_count < 0) {
				throw std::runtime_error("Couldn't pop negative indexed node.");
			}
			bool res = RemoveAt(idx - popped_count);
			if (!res) {
				throw std::runtime_error("Could not remove data at certain index");
			}
			popped_count++;
		}
		return popped_count; // same as indices.size()
	}
	bool RemoveAt(unsigned int index) {
		if (index < 0) {
			throw std::out_of_range("Out of bounds.");
		}
		else if (index == 0) {
			return RemoveHead();
		}
		if (!head) {
			throw std::runtime_error("Empty LinkedList. Could not remove at index.");
		}
		Node* match = GetNode(index);
		if (match == nullptr) {
			//throw std::out_of_range("Invalid index. Could not remove node.");
			return false;
		}
		if (!match->has_next()) { // cannot remove at this index.
			if (match == tail) { // is tail
				return RemoveTail();
			}
			return false;
		}
		if (!match->has_prev()) {
			throw std::runtime_error("Node should have a previous link (list-like)");
		}
		if (!match->prev->has_next()) {
			throw std::runtime_error("Previous node should have a link to the next (list-like)");
		}
		match->prev->next = match->next;
		match->next->prev = match->prev;
		delete match;
		return true;
	}
	void Clear() {
		if (!head) {
			throw std::runtime_error("Empty LinkedList. Could not clear.");
		}
		head->free_next_recursive();
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	// Accessors
	unsigned int NodeCount() const {
		if (!head) {
			return 0;
		}
		size_t count = 1;
		Node* next = head;
		while (next->has_next()) {
			next = next->next;
			count++;
		}
		return count;
	}
	void FindAll(std::vector<Node*>& out_data, const T& value) const {
		if (!head) {
			return;
		}
		for (Node* next = head; next != nullptr; next = next->next) {
			if (next->data == value) {
				out_data.push_back(next);
			}
		}
	}
	const Node* Find(const T& data) const {
		// gets first occurance of T
		if (!head) {
			return nullptr;
		}
		for (Node* next = head; next != nullptr; next = next->next) {
			if (next->data == data) {
				return next;
			}
		}
		return nullptr;
	}
	Node* Find(const T& data) {
		// gets first occurance of T
		if (!head) {
			return nullptr;
		}
		for (Node* next = head; next != nullptr; next = next->next) {
			if (next->data == data) {
				return next;
			}
		}
		return nullptr;
	}
	const Node* GetNode(unsigned int index) const {
		if (!head) {
			throw std::runtime_error("Empty LinkedList. Could not get node at index.");
		}
		if (index < 0) {
			throw std::out_of_range("Index out of bounds of LinkedList");
		}
		size_t idx = 0;
		Node* next = head;
		for (; idx < index; idx++) {
			if (!next->has_next()) {
				//throw std::out_of_range("Index out of bounds of LinkedList");
				return nullptr;
			}
			next = next->next;
		}
		return next;
	}
	Node* GetNode(unsigned int index) {
		if (!head) {
			throw std::runtime_error("Empty LinkedList. Could not get node at index.");
		}
		if (index < 0) {
			throw std::out_of_range("Index out of bounds of LinkedList");
		}
		size_t idx = 0;
		Node* next = head;
		for (; idx < index; idx++) {
			if (!next->has_next()) {
				//throw std::out_of_range("Index out of bounds of LinkedList");
				return nullptr;
			}
			next = next->next;
		}
		return next;
	}
	Node* getHead() {
		return head;
	}
	const Node* getHead() const {
		return head;
	}
	Node* Head() {
		return head;
	}
	const Node* Head() const {
		return head;
	}
	Node* getTail() { // just in case
		return tail;
	}
	const Node* getTail() const { // just in case
		return tail;
	}
	Node* Tail() {
		return tail;
	}
	const Node* Tail() const {
		return tail;
	}
	// Behaviors
	std::vector<Node*> as_vec() const {
		std::vector<Node*> vec;
		if (!head) {
			return vec;
		}
		Node* curr = head;
		vec.push_back(curr);
		while (curr->has_next()) {
			curr = curr->next;
			vec.push_back(curr);
		}
		return vec;
	}
	static std::vector<Node*> iter_from_node(const Node* node) {
		std::vector<Node*> vec;
		if (!node->head) {
			return vec;
		}
		Node* curr = node->head;
		vec.push_back(curr);
		while (curr->has_next()) {
			curr = curr->next;
			vec.push_back(curr);
		}
		return vec;
	}
	void PrintForward() const { // skip the boilerplate
		PrintForwardRecursive(head);
	}
	void PrintReverse() const {
		PrintReverseRecursive(tail);
	}
	void PrintForwardRecursive(const Node* node) const {
		if (!node) {
			return;
		}
		std::cout << node->data << '\n';
		if (node->has_next()) {
			PrintForwardRecursive(node->next);
		}
	}
	void PrintReverseRecursive(const Node* node) const {
		if (!node) {
			return;
		}
		std::cout << node->data << '\n';
		if (node->has_prev()) {
			PrintReverseRecursive(node->prev);
		}
	}
	// Operators
	const T& operator[](unsigned int index) const {
		Node* match = GetNode(index);
		if (!match) {
			throw std::runtime_error("Could not retrieve LinkedList at index");
		}
		return match->data;
	}
	T& operator[](unsigned int index) {
		Node* match = GetNode(index);
		if (!match) {
			throw std::runtime_error("Could not retrieve LinkedList at index");
		}
		return match->data;
	}
	bool operator==(const LinkedList<T>& rhs) const {
		if (!head || !rhs.head) {
			return false;
		}
		Node* lhs_node = head;
		Node* rhs_node = rhs.head;
		while (true) {
			if (lhs_node->data != rhs_node->data) {
				return false;
			}
			if (!lhs_node->has_next() && !rhs_node->has_next()) {
				break;
			} else if (!lhs_node->has_next() || !rhs_node->has_next()) {
				return false;
			}
			lhs_node = lhs_node->next;
			rhs_node = rhs_node->next;
		}
		return true;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (head) {
			head->free_next_recursive();
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		if (rhs.head) {
			head = Node::deep_copy_from(rhs.head, nullptr);
			tail = Node::get_tail(head);
		}
		return *this;
	}
};
