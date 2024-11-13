#include <iostream>
#include <vector>
#include <fstream> // Failo operacijoms
#include "user.h"
#include "transaction.h"
#include "utxo.h"
#include "block.h"
#include <unordered_map>
#include <chrono> // Laiko matavimui
#include <thread> // Lygiagretumui
#include <omp.h> // Lygiagrečiam kasimui su OpenMP

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

// Funkcija išvalyti failus
void clearFiles() {
    std::ofstream blockFile("block.txt", std::ios::trunc);
    std::ofstream usersFile("users.txt", std::ios::trunc);
    std::ofstream userNewFile("user_new.txt", std::ios::trunc);
    std::ofstream transactionUTXOFile("transaction_utxo.txt", std::ios::trunc);

    if (!blockFile.is_open() || !usersFile.is_open() || !userNewFile.is_open() || !transactionUTXOFile.is_open()) {
        std::cerr << "Klaida atidarant failus išvalymui!\n";
        return;
    }

    blockFile.close();
    usersFile.close();
    userNewFile.close();
    transactionUTXOFile.close();
}

int main() { 

    // Išvalyti failus programos pradžioje
    clearFiles();
    int difficulty = 1;
    omp_set_num_threads(4);
    char generateUsers;
    char generateTransactions;
    char generateUntilNoTransactions;
    const int userCount = 1000;
    const int transactionCount = 10000;
    const int transactionsPerBlock = 10; // Kiek transakcijų bus kiekviename bloke
    std::vector<User> users;
    std::vector<Transaction> generatedTransactions; // Masyvas sugeneruotoms transakcijoms
    std::unordered_map<std::string, double> balances; // Žemėlapis balansams
    char parallelMining;

    std::cout << "Ar norite naudoti lygiagretu bloku kasima? (t/n): ";
    std::cin >> parallelMining;

    // Klausia apie vartotojų generavimą
    std::cout << "Ar norite sugeneruoti vartotojus? (t/n): ";
    std::cin >> generateUsers;

    if (generateUsers == 't' || generateUsers == 'T') {
        users = generateUsersList(userCount);

        // Sukuriame balansus vartotojams
        for (const auto& user : users) {
            balances[user.publicKey] = user.balance;
        }
    } else {
        std::cout << "Vartotojai nebuvo sugeneruoti.\n";
    }

    // Klausia apie transakcijų generavimą
    std::cout << "Ar norite sugeneruoti transakcijas? (t/n): ";
    std::cin >> generateTransactions;

    if (generateTransactions == 't' || generateTransactions == 'T') {
        if (users.empty()) {
            std::cout << "Transakcijos negali būti sugeneruotos, nes nera vartotoju.\n";
        } else {
            UTXO::initializeUTXOListFromUsers(users);
            if (UTXO::utxoPool.empty()) {
                std::cout << "Nera pakankamai UTXO transakcijoms. Nepavyko generuoti transakcijų.\n";
            } else {
                std::cout << "Generuojamos transakcijos... (" << transactionCount << " transakciju)\n";
                generatedTransactions = generateTransactionsList(transactionCount, users, balances);
            }
        }
    } else {
        std::cout << "Transakcijos nebuvo sugeneruotos.\n";
    }

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
            Block newBlock(previousHash, blockTransactions, difficulty);
            newBlock.mineBlock();

            blockchain.push_back(newBlock);
            std::cout << "Blokas #" << blockchain.size() << " buvo sekmingai iskastas su " << blockTransactions.size() << " transakcijomis.\n";

            updateUserBalances(users);
        }
    } else {
        if (parallelMining == 't' || parallelMining == 'T') {
            int blockCount;
    std::cout << "Kiek bloku norite sugeneruoti? ";
    std::cin >> blockCount;

    #pragma omp parallel for
    for (int i = 0; i < blockCount && !generatedTransactions.empty(); ++i) {
         std::vector<Transaction> blockTransactions;

        // Surenkame transakcijas blokui
        #pragma omp critical
        {
            for (int j = 0; j < transactionsPerBlock && !generatedTransactions.empty(); ++j) {
                blockTransactions.push_back(generatedTransactions.back());
                generatedTransactions.pop_back();
            }
        }

        std::string previousHash = (i == 0) ? "2" : blockchain.back().calculateHash();
        Block newBlock(previousHash, blockTransactions, difficulty);

        // Lygiagrečiai kasama bloką
        newBlock.mineBlock();

        // Atnaujiname blokų grandinę ir balansus po bloko iškasimo
        #pragma omp critical
        {
            blockchain.push_back(newBlock);
            std::cout << "Blokas #" << (i + 1) << " buvo sekmingai iskastas su " << blockTransactions.size() << " transakcijomis.\n";
            updateUserBalances(users);
        }
        } }else {
            int blockCount;
            std::cout << "Kiek bloku norite sugeneruoti? ";
            std::cin >> blockCount;

            char testMode;
            std::cout << "Ar norite atlikti bandymą? (t/n): ";
            std::cin >> testMode;

            if (testMode == 't' || testMode == 'T') {
                int maxDurationMs;
                std::cout << "Per kiek ms norite generuoti? ";
                std::cin >> maxDurationMs;

                bool blockGeneratedInTime = false;

                for (int i = 0; i < blockCount && !generatedTransactions.empty(); ++i) {
                    auto start = std::chrono::high_resolution_clock::now();

                    std::vector<Transaction> blockTransactions;
                    for (int j = 0; j < transactionsPerBlock && !generatedTransactions.empty(); ++j) {
                        blockTransactions.push_back(generatedTransactions.back());
                        generatedTransactions.pop_back();
                    }

                    std::string previousHash = (i == 0) ? "2" : blockchain.back().calculateHash();
                    Block newBlock(previousHash, blockTransactions, difficulty);
                    newBlock.mineBlock();

                    auto now = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration<double, std::milli>(now - start).count();

                    if (duration > maxDurationMs) {
                        std::cout << "Laiko limitas virsytas, nutraukiame generavima.\n";
                        break;
                    }

                    blockchain.push_back(newBlock);
                    std::cout << "Blokas #" << (i + 1) << " buvo sekmingai iskastas su " << blockTransactions.size() << " transakcijomis per " << duration << " ms.\n";
                    updateUserBalances(users);
                    blockGeneratedInTime = true;
                }

                if (!blockGeneratedInTime) {
                    std::cout << "Nepavyko sugeneruoti ne vieno bloko per nurodyta laika.\n";
                }
            } else {
                for (int i = 0; i < blockCount && !generatedTransactions.empty(); ++i) {
                    std::vector<Transaction> blockTransactions;

                    for (int j = 0; j < transactionsPerBlock && !generatedTransactions.empty(); ++j) {
                        blockTransactions.push_back(generatedTransactions.back());
                        generatedTransactions.pop_back();
                    }

                    std::string previousHash = (i == 0) ? "2" : blockchain.back().calculateHash();
                    Block newBlock(previousHash, blockTransactions, difficulty);
                    newBlock.mineBlock();

                    blockchain.push_back(newBlock);
                    std::cout << "Blokas #" << (i + 1) << " buvo sekmingai iskastas su " << blockTransactions.size() << " transakcijomis.\n";
                    updateUserBalances(users);
                }
            }
        }
    }

    std::cout << "Programos vykdymas baigtas.\n";
    return 0;
    
}
