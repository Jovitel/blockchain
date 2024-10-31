#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include "block.h"

class Blockchain {
public:
    Blockchain();
    void addBlock(Block newBlock);
    Block getLatestBlock() const;
    void printBlockchain() const;
    int getDifficulty() const;

private:
    std::vector<Block> chain;
    Block createGenesisBlock() const; // Deklaruokite kaip const
    int difficulty;
};

#endif
