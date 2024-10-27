// blockchain.cpp
#include "blockchain.h"
#include <iostream>

// Konstruktorius
Blockchain::Blockchain(int difficulty)
    : difficulty(difficulty) {
    // Pridedame pradžios bloką (Genesis Block)
    chain.push_back(createGenesisBlock());
}

// Pradinis blokas
Block Blockchain::createGenesisBlock() const {
    return Block(1, "0", difficulty); // Versija 1, ankstesnio bloko maišos reikšmė "0"
}

// Paskutinio bloko gavimas
Block Blockchain::getLatestBlock() const {
    return chain.back();
}

// Bloko pridėjimas prie grandinės
void Blockchain::addBlock(Block newBlock) {
    newBlock.previousBlockHash = getLatestBlock().currentBlockHash; // Nustatome ankstesnio bloko maišą
    newBlock.mineBlock(); // Atliekame kasimą
    if (isBlockValid(newBlock, getLatestBlock())) {
        chain.push_back(newBlock);
        std::cout << "Blokas pridėtas: " << newBlock.currentBlockHash << std::endl;
    } else {
        std::cout << "Blokas negaliojantis, nepridėtas." << std::endl;
    }
}

// Bloko galiojimo tikrinimas
bool Blockchain::isBlockValid(const Block& newBlock, const Block& previousBlock) const {
    if (newBlock.previousBlockHash != previousBlock.currentBlockHash) {
        return false;
    }
    if (newBlock.calculateHash() != newBlock.currentBlockHash) {
        return false;
    }
    return true;
}

// Blokų grandinės spausdinimas
void Blockchain::printBlockchain() const {
    for (const auto& block : chain) {
        std::cout << "Bloko maišos reikšmė: " << block.currentBlockHash << std::endl;
        std::cout << "Ankstesnio bloko maišos reikšmė: " << block.previousBlockHash << std::endl;
        std::cout << "Transakcijų skaičius: " << block.transactions.size() << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
}
