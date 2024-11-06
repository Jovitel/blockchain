
#include "utxo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream> // Pridėta norint rašyti į failą

std::vector<UTXO> UTXO::utxoPool;

void UTXO::initializeUTXOListFromUsers(const std::vector<User>& users) {
    // Išvalome failą prieš rašymą
    std::ofstream outFile("transaction_utxo.txt");
    if (!outFile.is_open()) {
        std::cerr << "Klaida atidarant failą rašymui!\n";
        return;
    }
    outFile.close(); // Uždarykite failą, kad jis būtų tuščias

    for (const auto& user : users) {
        if (user.balance > 0) {
            createUTXO(user.publicKey, user.balance);
        }
    }
    std::cout << "Pradinis UTXO sarasas sukurtas is vartotoju balansu.\n";
}

void UTXO::createUTXO(const std::string& publicKey, int amount) {
    UTXO newUTXO = { publicKey, amount };
    utxoPool.push_back(newUTXO);
    
    // Rašyti informaciją į failą
    std::ofstream outFile("transaction_utxo.txt", std::ios::app);
    if (outFile.is_open()) {
       // outFile << "Sukurtas naujas UTXO: " << publicKey << ", Suma: " << amount << "\n";
        outFile.close();
    } else {
        std::cerr << "Klaida atidarant failą rašymui!\n";
    }
}

void UTXO::removeUTXO(const UTXO& utxo) {
    for (auto it = utxoPool.begin(); it != utxoPool.end(); ++it) {
        if (it->publicKey == utxo.publicKey && it->amount == utxo.amount) {
            utxoPool.erase(it);
            
            // Rašyti informaciją į failą
            std::ofstream outFile("transaction_utxo.txt", std::ios::app);
            if (outFile.is_open()) {
              //  outFile << "Pašalintas UTXO: " << utxo.publicKey << ", Suma: " << utxo.amount << "\n";
                outFile.close();
            } else {
                std::cerr << "Klaida atidarant failą rašymui!\n";
            }
            break;
        }
    }
}

