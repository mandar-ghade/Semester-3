#include "ContactBook.h"

int main() {
	Contact Roland("Roland", "456-789-0123"), Andres("Andres", "123-456-7890"), George("George", "123-456-7890");;
	Contact Lily("Lily", "123-456-7890"), Justin("Justin", "123-456-7890");
	std::vector<Contact*> contacts_group1 {
		&Roland,
		&Andres,
		&George,
	};
	std::vector<Contact*> contacts_group2 {
		&Lily,
		&Justin,
	};
	ContactBook book;
	ContactBook book2;
	book.AddContacts(contacts_group1);
	book2.AddContacts(contacts_group2);
	book += book2;
	book.Display();
	return 0;
}
