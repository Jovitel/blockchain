#include <iostream>
#include <vector>
#include <fstream> // Failo operacijoms
#include "user.h"
#include "transaction.h"
#include "utxo.h"
#include "block.h"
#include <unordered_map>

// Deklaruojame funkciją, kad galėtume nuskaityti transakcijas iš failo
std::vector<Transaction> readTransactionsFromFile(const std::string& filename);

// Funkcija, kuri atnaujina vartotojų balansus ir įrašo juos į failą
void updateUserBalances(const std::vector<User>& users) {
    std::ofstream outFile("user_new.txt", std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Klaida atidarant failą rašymui!\n";
        return;
    }

    for (const auto& user : users) {
        outFile << "Vartotojas: " << user.publicKey << ", Balansas: " << user.balance << "\n";
    }

    outFile.close();
}

int main() {
    char generateUsers;
    char generateTransactions;
    char generateUntilNoTransactions;
    const int userCount = 1000;
    const int transactionCount = 10000;
    const int transactionsPerBlock = 10; // Apibrėžkite čia, kiek transakcijų bus kiekviename bloke
    std::vector<User> users;
    std::vector<Transaction> generatedTransactions; // Masyvas sugeneruotoms transakcijoms
    std::unordered_map<std::string, double> balances; // Žemėlapis balansams

    // Klausia apie vartotojų generavimą
    std::cout << "Ar norite sugeneruoti vartotojus? (t/n): ";
    std::cin >> generateUsers;

    if (generateUsers == 't' || generateUsers == 'T') {
        users = generateUsersList(userCount);
        
        // Sukuriame balansus vartotojams
        for (const auto& user : users) {
            balances[user.publicKey] = user.balance;  // Priskiriame balansą vartotojui
        }
    } else {
        std::cout << "Vartotojai nebuvo sugeneruoti.\n";
    }

    // Klausia apie transakcijų generavimą
    std::cout << "Ar norite sugeneruoti transakcijas? (t/n): ";
    std::cin >> generateTransactions;

    if (generateTransactions == 't' || generateTransactions == 'T') {
        if (users.empty()) {
            std::cout << "Transakcijos negali būti sugeneruotos, nes nera vartotojų.\n";
        } else {
            UTXO::initializeUTXOListFromUsers(users);
            if (UTXO::utxoPool.empty()) {
                std::cout << "Nera pakankamai UTXO transakcijoms. Nepavyko generuoti transakciju.\n";
            } else {
                std::cout << "Generuojamos transakcijos... (" << transactionCount << " transakciju)\n";
                // Sugeneruojame transakcijas ir saugome jas masyve
                generatedTransactions = generateTransactionsList(transactionCount, users, balances);
            }
        }
    } else {
        std::cout << "Transakcijos nebuvo sugeneruotos.\n";
    }

    // Naudojame sugenerotas transakcijas generuoti blokus
    std::vector<Block> blockchain;

    // Naujas pasirinkimas generuoti blokus iki kol nėra neįtrauktų transakcijų
    std::cout << "Ar norite generuoti blokus tol, kol yra neitrauktu transakciju? (t/n): ";
    std::cin >> generateUntilNoTransactions;

    if (generateUntilNoTransactions == 't' || generateUntilNoTransactions == 'T') {
        while (!generatedTransactions.empty()) {
            std::vector<Transaction> blockTransactions;

            for (int j = 0; j < transactionsPerBlock && !generatedTransactions.empty(); ++j) {
                blockTransactions.push_back(generatedTransactions.back());
                generatedTransactions.pop_back();
            }

            std::string previousHash = blockchain.empty() ? "2" : blockchain.back().calculateHash();
            Block newBlock(previousHash, blockTransactions, 0); // 2 - sunkumo lygis
            newBlock.mineBlock();

            blockchain.push_back(newBlock);
            std::cout << "Blokas #" << blockchain.size() << " buvo sekmingai iskastas su " << blockTransactions.size() << " transakcijomis.\n";

            // Atlikti vartotojų balansų atnaujinimą po bloko maišos radimo
            updateUserBalances(users);
        }
    } else {
        // Jei vartotojas nenori generuoti blokus iki kol nėra neįtrauktų transakcijų
        int blockCount;
        std::cout << "Kiek bloku norite sugeneruoti? ";
        std::cin >> blockCount;

        for (int i = 0; i < blockCount && !generatedTransactions.empty(); ++i) {
            std::vector<Transaction> blockTransactions;

            for (int j = 0; j < transactionsPerBlock && !generatedTransactions.empty(); ++j) {
                blockTransactions.push_back(generatedTransactions.back());
                generatedTransactions.pop_back();
            }

            std::string previousHash = (i == 0) ? "2" : blockchain.back().calculateHash();
            Block newBlock(previousHash, blockTransactions, 0); // 2 - sunkumo lygis
            newBlock.mineBlock();

            blockchain.push_back(newBlock);
            std::cout << "Blokas #" << (i + 1) << " buvo sekmingai iskastas su " << blockTransactions.size() << " transakcijomis.\n";

            // Atlikti vartotojų balansų atnaujinimą po bloko maišos radimo
            updateUserBalances(users);
        }
    }

    std::cout << "Programos vykdymas baigtas.\n";
    return 0;
}
