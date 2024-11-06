#ifndef UTXO_H
#define UTXO_H

#include <string>
#include <vector>
#include "user.h" // Įsitikinkite, kad turite šį failą su User struktūra

struct UTXO {
    std::string publicKey;
    int amount;

    static std::vector<UTXO> utxoPool;

    static void createUTXO(const std::string& publicKey, int amount);
    static void removeUTXO(const UTXO& utxo);
    static UTXO getRandomUTXO();
    static void initializeUTXOListFromUsers(const std::vector<User>& users); // Pradinio sąrašo funkcija
    static void createCoinbaseUTXO(const std::string& minerPublicKey, int rewardAmount); // Coinbase funkcija
};

#endif // UTXO_H
