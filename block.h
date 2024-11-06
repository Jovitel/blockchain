#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "transaction.h"

class Block {
public:
    std::string previousHash;
    std::string merkleRoot;
    std::vector<Transaction> transactions;
    time_t timestamp;
    int nonce;
    int difficulty;
    std::string version; // Pridėtas versijos kintamasis

    Block(std::string prevHash, const std::vector<Transaction>& txs, int diff);

    std::string calculateHash() const;
    void mineBlock();

private:
    std::string createMerkleRoot() const;
};

#endif // BLOCK_H
