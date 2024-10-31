#include "block.h"
#include "blockchain.h"
#include "transaction.h"
#include <vector>

int main() {
    Blockchain blockchain;

    // Pavyzdinis transakcijų sąrašas
    std::vector<Transaction> transactions;
    transactions.push_back(Transaction("SenderPublicKey1", "ReceiverPublicKey1", 100));
    transactions.push_back(Transaction("SenderPublicKey2", "ReceiverPublicKey2", 200));

    // Naujo bloko kūrimas ir pridėjimas
    Block newBlock(blockchain.getLatestBlock().currentBlockHash, transactions, blockchain.getDifficulty());
    blockchain.addBlock(newBlock); // Pridedame bloką į blokų grandinę

    // Spausdina visą blokų grandinę
    blockchain.printBlockchain();

    return 0;
}
