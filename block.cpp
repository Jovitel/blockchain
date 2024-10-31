#include "block.h"
#include <iostream>
#include <sstream>
#include <ctime>

Block::Block(std::string prevHash, std::vector<Transaction> tx, int diffTarget) 
    : previousBlockHash(prevHash), currentBlockHash(""), merkleRootHash(""), timestamp(0), version(1), nonce(0), difficultyTarget(diffTarget), transactions(tx) {
    timestamp = time(nullptr);
    merkleRootHash = "MerkleRootExample"; // Turėtų būti generuojama pagal transakcijas
    currentBlockHash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << previousBlockHash << merkleRootHash << timestamp << version << nonce;
    return std::to_string(std::hash<std::string>{}(ss.str())); // Laikinas hash'o generavimas
}

void Block::mineBlock() {
    std::string target(difficultyTarget, '0');
    do {
        nonce++;
        currentBlockHash = calculateHash();
    } while (currentBlockHash.substr(0, difficultyTarget) != target);
    std::cout << "Išminuotas blokas: " << currentBlockHash << std::endl;
}

void Block::printBlock() const {
    std::cout << "Bloko maišos reikšmė: " << currentBlockHash << std::endl;
    std::cout << "Ankstesnio bloko maišos reikšmė: " << previousBlockHash << std::endl;
    std::cout << "Merkle šaknies maišos reikšmė: " << merkleRootHash << std::endl;
    std::cout << "Nonce: " << nonce << std::endl;
    std::cout << "Timestamp: " << timestamp << std::endl;
    std::cout << "Versija: " << version << std::endl;

    // Spausdiname transakcijas
    std::cout << "Transakcijos:" << std::endl;
    for (const auto& transaction : transactions) {
        std::cout << "  - " << transaction.transactionID << ": " << transaction.amount << " (iš: " << transaction.senderPublicKey << ", į: " << transaction.receiverPublicKey << ")" << std::endl; // Išvedame kiekvieną transakciją
    }
}
