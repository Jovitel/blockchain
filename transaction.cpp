#include "transaction.h"
#include <iostream>
#include <vector>
#include <cstdlib> // dėl rand()
#include <ctime>
#include <fstream> // ofstream

std::vector<Transaction> generateTransactionsList(int numberOfTransactions, const std::vector<User>& users, const std::unordered_map<std::string, double>& balances) {
    srand(static_cast<unsigned>(time(0))); // Inicializuojame atsitiktinių skaičių generatorių
    std::vector<Transaction> generatedTransactions;
    std::ofstream outFile("transaction_utxo.txt", std::ios::trunc);

    if (!outFile.is_open()) {
        std::cerr << "Klaida atidarant failą rašymui!\n";
        return {};
    }

    for (int i = 0; i < numberOfTransactions; ++i) {
        std::string sender = users[rand() % users.size()].publicKey;
        std::string receiver = users[rand() % users.size()].publicKey;
        int amount = rand() % 100 + 1; // Atsitiktinė suma

        if (balances.at(sender) < amount) {
            outFile << "Siuntėjo balansas nepakankamas.\n";
            continue;
        }

        Transaction transaction(sender, receiver, amount);
        if (transaction.checkTransactionHash()) {
            generatedTransactions.push_back(transaction);
            outFile << "Transakcija: " << transaction.transactionID
                    << ", Siuntėjas: " << transaction.senderPublicKey
                    << ", Gavėjas: " << transaction.receiverPublicKey
                    << ", Suma: " << transaction.amount << "BTC" << "\n";
        } else {
            outFile << "Transakcijos maišas neteisingas.\n";
        }
    }

    outFile.close();
    return generatedTransactions;
}