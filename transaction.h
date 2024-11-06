#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include "utxo.h"
#include "user.h"
#include <functional> // std::hash

struct Transaction {
    std::string transactionID;
    std::string senderPublicKey;
    std::string receiverPublicKey;
    int amount;

    // Konstruktoras
    Transaction(const std::string& sender, const std::string& receiver, int amt)
        : senderPublicKey(sender), receiverPublicKey(receiver), amount(amt) {
        transactionID = generateTransactionID(); // Automatiškai sugeneruojame transakcijos ID
    }

    // Generuoja transakcijos ID (naudojama kaip maišas)
    std::string generateTransactionID() const {
        return std::to_string(std::hash<std::string>{}(senderPublicKey + receiverPublicKey + std::to_string(amount)));
    }

    // Funkcija tikrina, ar transakcijos maišas teisingas
    bool checkTransactionHash() const {
        return transactionID == generateTransactionID();
    }
};

// Funkcijos deklaracija
std::vector<Transaction> generateTransactionsList(int numberOfTransactions, const std::vector<User>& users, const std::unordered_map<std::string, double>& balances);

#endif // TRANSACTION_H
