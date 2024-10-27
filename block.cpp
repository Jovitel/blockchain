// block.cpp
#include "block.h"
#include "hash_function.h" // Naudokite savo maišos funkciją
#include <sstream>

// Konstruktorius
Block::Block(int index, const std::string& previousBlockHash, int difficulty)
    : index(index) {
    header.previousBlockHash = previousBlockHash;
    header.difficulty = difficulty;
    header.timestamp = std::time(nullptr);
    header.version = 1; // Nustatoma versija
    header.nonce = 0;
}

// Bloko maišos skaičiavimas
std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << header.version << header.previousBlockHash << header.merkleRootHash
       << header.timestamp << header.nonce << header.difficulty;

    return generateHash(ss.str()); // Naudojama jūsų maišos funkcija
}

// Bloko kasimo funkcija
void Block::mineBlock() {
    header.merkleRootHash = calculateMerkleRoot(); // Apskaičiuojama Merkle šaknis
    std::string hash;
    do {
        header.nonce++;
        hash = calculateHash();
    } while (hash.substr(0, header.difficulty) != std::string(header.difficulty, '0'));

    currentBlockHash = hash;
}

// Merkle šaknies apskaičiavimas
std::string Block::calculateMerkleRoot() const {
    if (transactions.empty()) return "";

    std::vector<std::string> merkleTree;
    for (const auto& tx : transactions) {
        merkleTree.push_back(tx.transactionID);
    }

    while (merkleTree.size() > 1) {
        if (merkleTree.size() % 2 != 0) {
            merkleTree.push_back(merkleTree.back());
        }

        std::vector<std::string> newLayer;
        for (size_t i = 0; i < merkleTree.size(); i += 2) {
            newLayer.push_back(generateHash(merkleTree[i] + merkleTree[i + 1]));
        }
        merkleTree = newLayer;
    }
    return merkleTree.front();
}
