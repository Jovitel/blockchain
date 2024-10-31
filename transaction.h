#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>

class Transaction {
public:
    std::string transactionID;
    std::string senderPublicKey;
    std::string receiverPublicKey;
    int amount;

    Transaction(std::string sender, std::string receiver, int amount);
    void printTransaction() const; // Naujas metodas
};

#endif
