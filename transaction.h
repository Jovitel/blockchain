// transaction.h
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    // Transakcijos duomenys
    std::string transactionID;
    std::string senderPublicKey;
    std::string receiverPublicKey;
    double amount;

    // Konstruktorius
    Transaction(const std::string& sender, const std::string& receiver, double amount);

    // Funkcija transakcijos maišos skaičiavimui
    std::string calculateTransactionHash() const;
};

#endif // TRANSACTION_H
