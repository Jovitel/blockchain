#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    std::string senderPublicKey;
    std::string receiverPublicKey;
    int amount;
    std::string transactionID;

    Transaction(std::string sender, std::string receiver, int amount);
    void printTransaction() const;
};

#endif
