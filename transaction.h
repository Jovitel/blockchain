#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <unordered_map>
#include "user.h"
#include "hash_function.h"  // Pridėta dėl maišos funkcijos

struct Transaction {
    std::string transactionID;
    std::string senderPublicKey;
    std::string receiverPublicKey;
    int amount;

    // Konstruktoras
    Transaction(const std::string& sender, const std::string& receiver, int amt)
        : senderPublicKey(sender), receiverPublicKey(receiver), amount(amt) {
        transactionID = generateTransactionID(); // Sugeneruojame transakcijos ID naudodami maišos funkciją
    }

    // Generuoja transakcijos ID naudodama maišos funkciją
    std::string generateTransactionID() const {
        std::string transactionData = senderPublicKey + receiverPublicKey;
        return generateHash(transactionData);  // Naudojame maišos funkciją
    }

    // Funkcija tikrina, ar transakcijos maišas teisingas
    bool checkTransactionHash() const {
        return transactionID == generateTransactionID();
    }
};

// Funkcijos deklaracija
std::vector<Transaction> generateTransactionsList(int numberOfTransactions, const std::vector<User>& users, const std::unordered_map<std::string, double>& balances);

#endif // TRANSACTION_H
