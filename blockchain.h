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

    std::vector<Block> chain; // Pakeista į public

private:
    Block createGenesisBlock() const; // Deklaruokite kaip const
    int difficulty;
};

#endif
