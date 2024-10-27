// block.h
#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <ctime>
#include "transaction.h"

// Bloko antraštė
struct BlockHeader {
    int version;                           // Blokų grandinės versija
    std::string previousBlockHash;         // Ankstesnio bloko maišos reikšmė
    std::string merkleRootHash;            // Merkle medžio šaknis (visų transakcijų maišos)
    std::time_t timestamp;                 // Laiko žyma
    int nonce;                             // Atsitiktinis skaičius (kasimui)
    int difficulty;                        // Sunkumo lygis (maišos sudėtingumas)
};

// Bloko struktūra
class Block {
public:
    BlockHeader header;                    // Bloko antraštė
    std::vector<Transaction> transactions; // Bloko turinys (transakcijos)
    std::string currentBlockHash;          // Šio bloko maišos reikšmė

    // Konstruktorius
    Block(int index, const std::string& previousBlockHash, int difficulty);

    // Funkcijos
    std::string calculateHash() const;     // Apskaičiuoti bloko maišą
    void mineBlock();                      // Kasti bloką
    std::string calculateMerkleRoot() const; // Apskaičiuoti Merkle šaknį

private:
    int index;                             // Bloko indeksas grandinėje
    std::string calculateBlockHeader() const;
};

#endif // BLOCK_H
