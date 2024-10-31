#include "block.h"
#include "blockchain.h"
#include "transaction.h"
#include <vector>
#include <iostream>
#include <fstream>

int main() {
    Blockchain blockchain;
    char generateMoreBlocks;
    int blocksToGenerate = 0;

    std::cout << "Ar norite generuoti naujus vartotojus, transakcijas? (t/n): ";
    std::cin >> generateMoreBlocks;

    std::vector<Transaction> transactions; // Deklaracija čia

    if (generateMoreBlocks == 't') {
        std::cout << "Generuojami vartotojai..." << std::endl;
        // Generuoti vartotojus ir įrašyti juos į failą "Vartotojai.txt"
        std::ofstream userFile("Vartotojai.txt");
        // Pavyzdiniai vartotojai
        userFile << "User1\nUser2\nUser3\n";
        userFile.close();

        std::cout << "Generuojamos transakcijos..." << std::endl;
        // Generuoti pavyzdines transakcijas
        transactions.push_back(Transaction("SenderPublicKey1", "ReceiverPublicKey1", 100));
        transactions.push_back(Transaction("SenderPublicKey2", "ReceiverPublicKey2", 200));
        transactions.push_back(Transaction("SenderPublicKey3", "ReceiverPublicKey3", 300));

        // Įrašyti transakcijas į failą "Transakcijos.txt"
        std::ofstream transactionFile("Transakcijos.txt");
        for (const auto& tx : transactions) {
            transactionFile << tx.transactionID << ": " << tx.amount << " (iš: " 
                            << tx.senderPublicKey << ", į: " << tx.receiverPublicKey << ")\n";
        }
        transactionFile.close();
    }

    std::cout << "Bloku generavimas prasideda..." << std::endl;
    std::cout << "Galima is kart paspausti keleta 't', kad iskasti keleta bloku." << std::endl;

    std::cout << "Kiek blokų norite sugeneruoti? (1-3): ";
    std::cin >> blocksToGenerate;

    for (int i = 0; i < blocksToGenerate; ++i) {
        std::cout << "Generuojamas blokas " << (i + 1) << "..." << std::endl;

        // Generuojame bloką su sukurtomis transakcijomis
        Block newBlock(blockchain.getLatestBlock().currentBlockHash, transactions, blockchain.getDifficulty());
        blockchain.addBlock(newBlock);
    }

    // Įrašyti vartotojų balansus į failą "NaujiVartotojuBalansai.txt"
    std::ofstream balanceFile("NaujiVartotojuBalansai.txt");
    // Čia turėtų būti kodo dalis, kuri atnaujina vartotojų balansus
    // Pavyzdžiui:
    balanceFile << "User1: 900\nUser2: 800\nUser3: 700\n";
    balanceFile.close();

    // Įrašyti informaciją apie blokus į failą "Blokai.txt"
    std::ofstream blocksFile("Blokai.txt");
    // Čia turėtų būti kodo dalis, kuri įrašo informaciją apie visus blokų
    for (const auto& block : blockchain.chain) {
        blocksFile << "Blokas: " << block.currentBlockHash << "\n";
        // Galima pridėti daugiau informacijos apie bloką
    }
    blocksFile.close();

    std::cout << "Pasirinkite viena veiksma is nurodytu zemiau." << std::endl;
    std::cout << "1. Ieškoti transakcijos pagal ID." << std::endl;
    std::cout << "2. Ieškoti bloko pagal ID." << std::endl;
    std::cout << "Bet koks kitas sakinis baigia programa." << std::endl;

    // Programa baigiama...
    return 0;
}
