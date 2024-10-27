// blockchain.h
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include "block.h"

class Blockchain {
public:
    // Blokų grandinės duomenys
    std::vector<Block> chain;
    int difficulty;

    // Konstruktorius
    Blockchain(int difficulty);

    // Funkcijos
    void addBlock(Block newBlock);
    Block createGenesisBlock() const;
    Block getLatestBlock() const;
    void printBlockchain() const;

private:
    // Patikrinimas, ar blokas yra galiojantis
    bool isBlockValid(const Block& newBlock, const Block& previousBlock) const;
};

#endif // BLOCKCHAIN_H
