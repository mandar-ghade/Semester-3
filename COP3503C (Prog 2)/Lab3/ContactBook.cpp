#include "ContactBook.h"
#include "math.h"

std::string to_lower(const std::string& old) {
	std::string lower;
	for (const char& c: old) {
		lower.push_back(std::tolower(c));
	}
	return lower;
}

Contact::Contact(
	std::string name, std::string number
): name(name), lowercase_name(to_lower(name)), number(number) {}

Contact::Contact(Contact* contact): 
	name(contact->name),
	lowercase_name(contact->lowercase_name),
	number(contact->number)
{}

std::string Contact::getName() const {
	return this->name;
}

std::string Contact::getNumber() const {
	return this->number;
}

void Contact::display() const {
	std::cout << this->name << ", " << this->number << '\n';
}

ContactBook::ContactBook() : curr_size(0) {}

ContactBook::ContactBook(ContactBook* book) {
	for (size_t i = 0; i < book->curr_size; i++) {
		contacts[i] = book->contacts[i];
	}
	curr_size = book->curr_size;
}

ContactBook::ContactBook(Contact* cts[MAX_SIZE], unsigned int curr_size) {
	for (size_t i = 0; i < curr_size; i++) {
		contacts[i] = cts[i];
	}
	this->curr_size = curr_size;
}

Contact* ContactBook::Find(const std::string entry) const {
	// not testing for duplicates
	for (size_t i = 0; i < curr_size; i++) {
		Contact* curr = contacts[i];
		if (curr->getName() == entry || curr->getNumber() == entry) {
			return curr;
		}
	}
	return nullptr;
}

size_t ContactBook::getObjectIndex(const Contact* obj) const {
	for (size_t i = 0; i < curr_size; i++) {
		Contact* c = contacts[i];
		if (c == obj ||  // checks mem address first
		   (c->getName() == obj->getName() && c->getNumber() == obj->getNumber())
		) return i;
	}
	throw std::runtime_error("Object not found in ContactBook");
}

void ContactBook::Add(Contact* obj) {
	if (curr_size == 100) {
		throw std::runtime_error("Cannot append to array, too long.");
	} else if (!getExists(obj)) { // checks duplicates
		contacts[curr_size++] = obj;
	}
}

void ContactBook::Add(Contact& obj) {
	Add(&obj);
}

void ContactBook::AddContacts(std::vector<Contact*> cts) {
	for (size_t i = 0; i < cts.size(); i++) {
		Add(cts.at(i)); // safety
	}
}

void ContactBook::shiftLeft(size_t start_idx) {
	// shifts array left by 1 [start_index, curr_size-1].
	--curr_size;
	for (size_t i = start_idx; i < curr_size; i++) {
		contacts[i] = contacts[i+1];
	}
	contacts[curr_size+1] = nullptr; // properly terminates last entry 
}

void ContactBook::Remove(Contact* obj) {
	// really unnecessary, and increases time complexity but the tests might pass unless I add this.
	if (!getExists(obj)) return;
	size_t idx = getObjectIndex(obj);
	contacts[idx] = nullptr;
	shiftLeft(idx);
}
void ContactBook::Remove(Contact& obj) {
	Remove(&obj);
}

void ContactBook::Display() const {
	for (size_t i = 0; i < curr_size; i++) {
		contacts[i]->display();
	}
}

bool Contact::operator<(const Contact& rhs) const {
	return this->lowercase_name < rhs.lowercase_name;
}

void ContactBook::Alphabetize() {
	std::sort(contacts, contacts + curr_size, [] (const Contact* lhs, const Contact* rhs) { //mm lambdas
		return *lhs < *rhs;
	});
};

bool ContactBook::getExists(const Contact* obj) const {
	for (size_t i = 0; i < curr_size; i++) {
		Contact* c = contacts[i];
		if (
			(obj == c) ||  // checks mem address first
			(c->getName() == obj->getName() && c->getNumber() == obj->getNumber())
		){
			return true;
		}
	}
	return false;
}

ContactBook& ContactBook::operator+=(Contact& obj) {
	Add(obj);
	return *this;
}

ContactBook& ContactBook::operator+=(ContactBook& book) {
	for (size_t i = 0; i < book.curr_size; i++) {
		Add(book.contacts[i]);
	}
	return *this;
}

ContactBook& ContactBook::operator-=(Contact& obj) {
	Remove(obj);
	return *this;
}

ContactBook& ContactBook::operator-=(ContactBook& book) {
	for (size_t i = 0; i < book.curr_size; i++) {
		Remove(book.contacts[i]);
	}
	return *this;
}

ContactBook ContactBook::operator+(ContactBook& book) {
	ContactBook new_book(this->contacts, this->curr_size);
	for (size_t i = 0; i < book.curr_size; i++) {
		new_book.Add(book.contacts[i]);
	}
	return new_book;
}

ContactBook ContactBook::operator-(ContactBook& book) {
	ContactBook new_book(this->contacts, this->curr_size);
	for (size_t i = 0; i < book.curr_size; i++) {
		new_book.Remove(book.contacts[i]);
	}
	return new_book;
}

bool ContactBook::operator==(ContactBook& book) {
	if (this->curr_size != book.curr_size) return false;
	for (size_t i = 0; i < book.curr_size; i++) {
		// if other book isn't in our db, bad bad bad 
		if (!getExists(book.contacts[i])) return false; 
	}
	return true;
}

bool ContactBook::operator!=(ContactBook& book) {
	if (this->curr_size != book.curr_size) return true;
	for (size_t i = 0; i < book.curr_size; i++) {
		// if other book exists in our db
		if (getExists(book.contacts[i])) return true; 
	}
	return false;
}

