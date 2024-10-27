#include "user.h"

// Konstruktorius
User::User(const std::string& name, const std::string& publicKey, double balance)
    : name(name), publicKey(publicKey), balance(balance) {}

// Balanso atnaujinimo funkcija
void User::updateBalance(double amount) {
    balance += amount;
}
