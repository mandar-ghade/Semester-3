#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <vector>
#include <sstream>
#include "BankAccount.h"

enum ACCOUNT_TYPE {
	Checkings,
	Savings,
	Investment,
};

struct AccountReader {
private:
	std::map<int, BankAccount*> account_by_id;
	std::map<std::string, BankAccount*> account_by_str;
	std::vector<BankAccount*> accounts;
public:
	void read_from_file(std::string file_path) {
		BankAccount* curr = nullptr;
		std::ifstream FILE(file_path);
		std::string line;
		int i = 0;
		while (getline(FILE, line)) {
			if (i == 0) { // accounts for column names
				i += 1;
				continue;
			}
			std::istringstream stream(line);
			std::string type_as_str;
			std::string name;
			std::string amount_as_str;
			std::string id_as_str;
			int type;
			float amount;
			int id;
			getline(stream, type_as_str, ',');
			getline(stream, name, ',');
			getline(stream, amount_as_str, ',');
			getline(stream, id_as_str, ',');
			try {
				type = std::stoi(type_as_str);
			} catch (std::invalid_argument) {
				throw std::runtime_error("Could not convert type to int!");
			};
			try {
				amount = std::stof(amount_as_str);
			} catch (std::invalid_argument) {
				throw std::runtime_error("Could not convert amount to float!");
			};
			try {
				id = std::stoi(id_as_str);
			} catch (std::invalid_argument) {
				throw std::runtime_error("Could not convert id to int!");
			};
			if (type == 1) {
				curr = new CheckingAccount(amount, id, name);
			} else if (type == 2) {
				curr = new SavingsAccount(amount, id, name);
			} else if (type == 3) {
				curr = new InvestmentAccount(amount, id, name);
			} else {
				throw std::runtime_error("Account type not recognized!");
			}
			this->accounts.push_back(curr);
			this->account_by_id.emplace(id, curr);
			this->account_by_str.emplace(name, curr);
		}
	}

	ACCOUNT_TYPE get_account_type(BankAccount* account) {
		auto investment_acc = dynamic_cast<InvestmentAccount*>(account);
		auto checking_acc = dynamic_cast<CheckingAccount*>(account);
		auto savings_acc = dynamic_cast<SavingsAccount*>(account);
		if (investment_acc) {
			return Investment;
		} else if (checking_acc) {
			return Checkings;
		} else if (savings_acc) {
			return Savings;
		} else {
			throw std::runtime_error("Account type not recognized while casting.");
		}
	}

	ACCOUNT_TYPE type_as_enum(int type) {
		if (type == 1) {
			return Checkings;
		} else if (type == 2) {
			return Savings;
		} else if (type == 3) {
			return Investment;
		} else {
			throw std::runtime_error("Account type not recognized");
		}
	}

	void display_all_accounts() {
		auto iter = this->accounts.begin();
		for (; iter != this->accounts.end(); iter++) {
			(*iter)->Display();
		}
	}

	std::vector<BankAccount*> accounts_by_type(int type) {
		std::vector<BankAccount*> vec;
		ACCOUNT_TYPE acc_type = type_as_enum(type);
		auto iter = this->accounts.begin();
		for (; iter != this->accounts.end(); iter++) {
			if (get_account_type(*iter) != acc_type) {
				continue;
			}
			vec.push_back(*iter);
		}
		return vec;
	}

	void display_accounts_by_type(int type) {
		std::vector<BankAccount*> vec = accounts_by_type(type);
		auto iter = vec.begin();
		for (; iter != vec.end(); iter++) {
			(**iter).Display();
		}
	}

    void operator()(std::string file_path) {
		this->read_from_file(file_path);
		std::cout << "1. Display all accounts" << '\n';
		std::cout << "2. Display all of account type" << '\n';
		std::cout << "3. Find account" << '\n';
		std::string optionS;
        int option;
        getline(std::cin, optionS);
		try {
			option = std::stoi(optionS);
		} catch (std::invalid_argument) {
			throw std::runtime_error("Could not convert option to int!");
		}
		std::vector<BankAccount*> matches;
		if (option == 1) {
			display_all_accounts();
		} else if (option == 2) {
			int type;
			std::cin >> type;
			display_accounts_by_type(type);
		} else if (option == 3) {
			BankAccount* account = nullptr;
			std::string identifier;
			int id;
			getline(std::cin, identifier);
			try {
				id = std::stoi(identifier);
				if (account_by_id.find(id) != account_by_id.end()) {
					account = account_by_id.at(id);
				}
			} catch (std::invalid_argument) {
				if (account_by_str.find(identifier) != account_by_str.end()) {
					account = account_by_str.at(identifier);
				}
			}
			if (account != nullptr) {
				account->Display();
			} else {
				std::cout << "Could not find account!\n";
			}
		} else {
			throw std::runtime_error("Option not found!");
		} 
    }
	~AccountReader() {
		for (size_t i = 0; i < this->accounts.size(); i++) {
			delete this->accounts[i];
		}
	}
};

int main(int argc, char** argv) {
	if (argc != 2) {
		throw std::runtime_error("Functor requires at least 1 argument");
	}
	std::string file_path(argv[1]);
	AccountReader reader;
	reader(file_path);
	return 0;
}
