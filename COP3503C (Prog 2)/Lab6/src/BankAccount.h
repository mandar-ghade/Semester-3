#pragma once
#include <string>

class BankAccount {
private:
	int id;
	std::string name;
public:
	BankAccount(int id, std::string name): id(id), name(name) {};
	std::string getName();
	int getID();
	virtual ~BankAccount() = default;
	virtual void Display() = 0;
	virtual void Deposit(float) = 0;
	virtual float getAmount() = 0;
};

class CheckingAccount: virtual public BankAccount {
private:
	float amount;
protected:
	void setAmount(float quantity);
public:
	CheckingAccount(float amount, int id, std::string name):
		BankAccount(id, name),
		amount(amount)
	{};
	virtual bool Withdraw(float quantity);
	void Display();
	void Deposit(float quantity);
	float getAmount();
};

class SavingsAccount: virtual public BankAccount {
private:
	float amount;
protected:
	void setAmount(float quantity);
public:
	SavingsAccount(float amount, int id, std::string name):
		BankAccount(id, name),
		amount(amount)
	{};
	bool Withdraw(float quantity);
	float CompoundEarnings(float percent);
	bool Transfer(CheckingAccount& checking_account, float quantity);
	void Display();
	void Deposit(float quantity);
	float getAmount();
};


class InvestmentAccount: public CheckingAccount, private SavingsAccount {
private:
public:
	InvestmentAccount(float amount, int id, std::string name): 
		BankAccount(id, name),
		CheckingAccount(0.f, id, name),
		SavingsAccount(amount, id, name)
	{};
	bool Withdraw(float quantity);
	float CompoundEarnings(float percent);
	bool Transfer(float percent);
	void Display();
	void Deposit(float quantity);
	float getAmount();
};

