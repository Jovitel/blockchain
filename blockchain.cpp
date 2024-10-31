#include "blockchain.h"
#include <iostream>

Blockchain::Blockchain() {
    difficulty = 2; // Nustatykite pradinį sunkumą
    chain.push_back(createGenesisBlock()); // Pridėti pradinį bloką
}

Block Blockchain::createGenesisBlock() const { // Grąžinimo tipas turi būti Block
    return Block("0", {}, difficulty); // Nustatykite pradinį bloką
}

Block Blockchain::getLatestBlock() const {
    return chain.back();
}

void Blockchain::addBlock(Block newBlock) {
    newBlock.previousBlockHash = getLatestBlock().currentBlockHash;
    newBlock.mineBlock();
    chain.push_back(newBlock);
}

void Blockchain::printBlockchain() const {
    std::cout << "Blokų grandinė:" << std::endl;
    for (const auto& block : chain) {
        block.printBlock();
        std::cout << std::endl; // Pridėti tarpą tarp blokų
    }
}

int Blockchain::getDifficulty() const {
    return difficulty; // Grąžinkite sunkumą
}
