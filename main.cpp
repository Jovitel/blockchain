// main.cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "blockchain.h"
#include "user.h"
#include "transaction.h"

const int NUM_USERS = 1000;      // Vartotojų skaičius
const int NUM_TRANSACTIONS = 10000; // Transakcijų skaičius

// Funkcija vartotojų generavimui
std::vector<User> generateUsers(int numUsers) {
    std::vector<User> users;
    for (int i = 0; i < numUsers; ++i) {
        std::string name = "User" + std::to_string(i + 1);
        std::string publicKey = "PublicKey" + std::to_string(i + 1);
        double balance = static_cast<double>(rand() % 1000001 + 100); // Atsitiktinis balansas nuo 100 iki 1,000,000
        users.emplace_back(name, publicKey, balance);
    }
    return users;
}

// Funkcija transakcijų generavimui
std::vector<Transaction> generateTransactions(const std::vector<User>& users, int numTransactions) {
    std::vector<Transaction> transactions;
    for (int i = 0; i < numTransactions; ++i) {
        const User& sender = users[rand() % users.size()];
        const User& receiver = users[rand() % users.size()];
        double amount = static_cast<double>(rand() % static_cast<int>(sender.balance) + 1); // Atsitiktinė suma
        transactions.emplace_back(sender.publicKey, receiver.publicKey, amount);
    }
    return transactions;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Atsitiktinių skaičių sėklos nustatymas

    // Sukuriame blokų grandinę su sunkumo lygiu
    Blockchain blockchain(4); // Sunkumo lygis (nulių skaičius maišo pradžioje)

    // Sugeneruojame vartotojus
    std::vector<User> users = generateUsers(NUM_USERS);
    std::cout << "Sugeneruota vartotojų: " << users.size() << std::endl;

    // Sugeneruojame transakcijas
    std::vector<Transaction> transactions = generateTransactions(users, NUM_TRANSACTIONS);
    std::cout << "Sugeneruota transakcijų: " << transactions.size() << std::endl;

    // Pridedame transakcijas į bloką
    Block newBlock(1, blockchain.getLatestBlock().currentBlockHash, blockchain.difficulty);
    
    // Pridėti atsitiktinai pasirinktas transakcijas
    for (int i = 0; i < 100; ++i) {
        if (i < transactions.size()) {
            newBlock.transactions.push_back(transactions[i]);
        }
    }

    // Pridedame naują bloką prie blokų grandinės
    blockchain.addBlock(newBlock);

    // Išvedame blokų grandinę
    blockchain.printBlockchain();

    return 0;
}
