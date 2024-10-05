#pragma once
#include <string>
#include <vector>

class Contact {
	const std::string name;
	const std::string lowercase_name;
	const std::string number;
public:
	Contact(std::string name, std::string number);
	Contact(Contact* contact);
	std::string getName() const; 
	std::string getNumber() const; 
	bool operator<(const Contact& rhs) const; 
	void display() const;
};

class ContactBook {
	static const int MAX_SIZE = 100;
	Contact* contacts[MAX_SIZE];
	unsigned int curr_size = 0;
public:
	ContactBook(); 
	ContactBook(ContactBook* book); 
	ContactBook(Contact* cts[MAX_SIZE], unsigned int curr_size); 
	Contact* Find(const std::string entry) const; 
	size_t getObjectIndex(const Contact* obj) const; 
	void Add(Contact* obj); 
	void Add(Contact& obj);
	void AddContacts(std::vector<Contact*> cts); 
	void shiftLeft(size_t start_idx); 
	void Remove(Contact* obj); 
	void Remove(Contact& obj); 
	void Display() const; 
	void Alphabetize();
	bool getExists(const Contact* obj) const;
	ContactBook& operator+=(Contact& obj);
	ContactBook& operator+=(ContactBook& book);
	ContactBook& operator-=(Contact& obj);
	ContactBook& operator-=(ContactBook& book);
	ContactBook operator+(ContactBook& book);
	ContactBook operator-(ContactBook& book);
	bool operator==(ContactBook& book);
	bool operator!=(ContactBook& book);
};

