#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include "transaction.h"

class Block {
public:
    std::string previousBlockHash;   // Ankstesnio bloko maišos reikšmė
    std::string currentBlockHash;    // Šio bloko maišos reikšmė
    std::string merkleRootHash;      // Merkle šaknies maišos reikšmė
    long timestamp;                   // Laiko žyma
    int version;                     // Bloko versija
    int nonce;                       // Atsitiktinis skaičius
    int difficultyTarget;            // Sudėtingumo lygis
    std::vector<Transaction> transactions; // Transakcijos

    // Konstruktoriai ir metodai
    Block(std::string prevHash, std::vector<Transaction> tx, int diffTarget);
    void mineBlock();
    std::string calculateHash() const;
    void printBlock() const; // Atnaujintas metodas
};

#endif
