// transaction.cpp
#include "transaction.h"
#include "hash_function.h" // Naudokite savo maišos funkciją
#include <sstream>

// Konstruktorius
Transaction::Transaction(const std::string& sender, const std::string& receiver, double amount)
    : senderPublicKey(sender), receiverPublicKey(receiver), amount(amount) {
    transactionID = calculateTransactionHash(); // Apskaičiuojame transakcijos ID
}

// Transakcijos maišos skaičiavimas
std::string Transaction::calculateTransactionHash() const {
    std::stringstream ss;
    ss << senderPublicKey << receiverPublicKey << amount;
    // Naudokite savo maišos funkciją
    return "hash_pavyzdys"; // Pakeiskite su realia maišos funkcija
}
