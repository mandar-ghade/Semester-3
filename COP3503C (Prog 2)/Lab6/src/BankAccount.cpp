#include <iomanip>
#include <iostream>
#include "BankAccount.h"

std::string BankAccount::getName() {
	return this->name;
}

int BankAccount::getID() {
	return this->id;
}

void CheckingAccount::setAmount(float quantity) {
	this->amount = quantity;
}

bool CheckingAccount::Withdraw(float quantity) {
	if (quantity < 0 || quantity > this->amount) return false;
	this->amount -= quantity;
	return true;
}

void CheckingAccount::Display() {
	std::cout << this->getName() << " (" << this->getID() << "):" << '\n';
	std::cout << "\tChecking Account: $" << std::fixed << std::setprecision(2) << this->getAmount() << '\n';
}

void CheckingAccount::Deposit(float quantity) {
	this->amount += quantity;
}

float CheckingAccount::getAmount() {
	return this->amount;
}

void SavingsAccount::setAmount(float quantity) {
	this->amount = quantity;
}

bool SavingsAccount::Withdraw(float quantity) {
	if (quantity < 0 || quantity > this->amount) return false;
	this->amount -= quantity;
	return true;
}

float SavingsAccount::CompoundEarnings(float percent) {
	if (percent < 0 || percent > 1) {
		throw std::runtime_error("Earnings were not compounded. (Percentage was incorrectly entered)");
	}
	float new_balance = this->amount*(1+percent);
	float earnings = new_balance - amount;
	this->amount = new_balance;
	return earnings;
}

bool SavingsAccount::Transfer(
	CheckingAccount& checking_account, 
	float quantity
) {
	if (!this->Withdraw(quantity)) {
		return false;
	}
	checking_account.Deposit(quantity);
	return true;
}

void SavingsAccount::Display() {
	std::cout << this->getName() << " (" << this->getID() << "):" << '\n';
	std::cout << "\tSavings Account: $" << std::fixed << std::setprecision(2) << this->getAmount() << '\n';
}

void SavingsAccount::Deposit(float quantity) {
	this->amount += quantity;
}

float SavingsAccount::getAmount() {
	return this->amount;
}

void InvestmentAccount::Display() {
	std::cout << this->getName() << " (" << this->getID() << "):" << '\n';
	std::cout << "\tTotal: $" << std::fixed << std::setprecision(2) << this->getAmount() << '\n';
	std::cout << "\t\tImmediate Funds: $" << std::fixed << std::setprecision(2) << CheckingAccount::getAmount() << '\n';
	std::cout << "\t\tInvestment: $" << std::fixed << std::setprecision(2) << SavingsAccount::getAmount() << '\n';
}

void InvestmentAccount::Deposit(float quantity) {
	SavingsAccount::Deposit(quantity);
}

float InvestmentAccount::getAmount() {
	return CheckingAccount::getAmount() +
		   SavingsAccount::getAmount();
}

bool InvestmentAccount::Withdraw(float quantity) {
	return CheckingAccount::Withdraw(quantity);
}

float InvestmentAccount::CompoundEarnings(float percent) {
	float earnings = SavingsAccount::CompoundEarnings(percent);
	if (!SavingsAccount::Withdraw(earnings)) {
		throw std::runtime_error("Could not withdraw from SavingsAccount.");
	}
	CheckingAccount::Deposit(earnings);
	return earnings;
}

bool InvestmentAccount::Transfer(float percent) {
	float earnings = SavingsAccount::CompoundEarnings(percent);
	if (!SavingsAccount::Withdraw(earnings)) {
		return false;
	}
	CheckingAccount::Deposit(earnings);
	return true;
}

