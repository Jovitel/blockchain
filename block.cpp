 #include "block.h" // Įtraukiama Block klasės antraštė
#include "hash_function.h" // Įtraukiama maišos funkcijos antraštė
#include <algorithm> // Įtraukiama algoritmų biblioteka
#include <iostream> // Įtraukiama įvesties/išvesties biblioteka
#include <sstream> // Įtraukiama stringstream biblioteka
#include <fstream> // Įtraukiama failų rašymo/įvedimo biblioteka

// Block klasės konstruktorius
Block::Block(std::string prevHash, const std::vector<Transaction>& txs, int diff)
    : previousHash(std::move(prevHash)), // Inicializuojame ankstesnio bloko maišą
      transactions(txs), // Inicializuojame transakcijas
      difficulty(diff), // Inicializuojame sunkumo lygį
      nonce(0), // Inicializuojame nonce (atsitiktinis skaičius) su 0
      version("v0.2") { // Inicializuojame versiją
    timestamp = std::time(nullptr); // Nustatome laiko žymę į dabartinį laiką
    merkleRoot = createMerkleRoot(); // Sukuriame Merkle šaknį
}

// Funkcija, kuri sukuria Merkle šaknį
std::string Block::createMerkleRoot() const {
    std::vector<std::string> hashes; // Vektorius maišų
    for (const auto& tx : transactions) {
        hashes.push_back(tx.transactionID); // Naudojame transakcijos ID kaip maišą
    }
    
    while (hashes.size() > 1) {
        std::vector<std::string> newHashes; // Vektorius naujiems maišams
        for (size_t i = 0; i < hashes.size(); i += 2) {
            if (i + 1 < hashes.size()) {
                newHashes.push_back(generateHash(hashes[i] + hashes[i + 1])); // Maišome du gretimus maišus
            } else {
                newHashes.push_back(hashes[i]); // Jei nelyginis skaičius, paskutinį paliekame
            }
        }
        hashes = std::move(newHashes); // Naujas maišų rinkinys
    }

    return hashes.empty() ? "" : hashes[0]; // Grąžiname pirmąjį maišą, jei yra
}

// Funkcija, kuri apskaičiuoja bloko maišą
std::string Block::calculateHash() const {
    std::stringstream ss; // Naudojame stringstream formuoti maišui
    ss << version << previousHash << merkleRoot << timestamp << nonce; // Pridedame visas reikiamas dalis
    return generateHash(ss.str()); // Generuojame ir grąžiname maišą
}

// Funkcija, kuri kasybos blokus
void Block::mineBlock() {
    std::string hashPrefix(difficulty, '0'); // Tikslas su difficulty nulių pradžioje
    std::string hash;
    nonce = 0;

    // Ciklas, kuris kartojasi tiek kartų, kiek yra difficulty
    for (int i = 0; i < difficulty; ++i) {
        hash = calculateHash(); // Apskaičiuojame maišą

        // Jei difficulty > 0, modifikuojame maišą:
        hash = "0" + hash.substr(0, hash.size() - 1); // Pridėti nulį priekyje ir pašalinti paskutinį simbolį

        // Užtikriname, kad maišas būtų 64 simbolių ilgio
        if (hash.size() > 64) {
            hash = hash.substr(0, 64); // Pašalinti per daug simbolių, jei jų yra daugiau nei 64
        }
    }

    // Užtikriname, kad maišas atitiktų difficulty
    while (hash.substr(0, difficulty) != hashPrefix) {
        hash = calculateHash(); // Apskaičiuojame maišą iš naujo
        for (int i = 0; i < difficulty; ++i) {
            hash = "0" + hash.substr(0, hash.size() - 1); // Pridėti nulį priekyje ir pašalinti paskutinį simbolį
            if (hash.size() > 64) {
                hash = hash.substr(0, 64); // Jei maišas per ilgas, sumažiname iki 64 simbolių
            }
        }
        nonce++; // Atnaujiname nonce kiekvieną kartą
    }

    timestamp = std::time(nullptr); // Nustatome laiko žymę

    // Rašome bloką į failą
    std::ofstream outFile("block.txt", std::ios::app); // Atidaryti failą su append režimu

    if (!outFile.is_open()) {
        std::cerr << "Klaida: Nepavyko atidaryti failo rašymui.\n";  // Pridedame klaidos pranešimą, jei failas neatidaromas
    } else {
        outFile << "Bloko maišos reikšmė: " << hash << "\n";
        outFile << "Ankstesnio bloko maišos reikšmė: " << previousHash << "\n";

        char buffer[100];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&timestamp));

        outFile << "Laiko žyma: " << buffer << "\n";
        outFile << "Versija: " << version << "\n";
        outFile << "Merkle šaknies maišas: " << merkleRoot << "\n";
        outFile << "Nonce: " << nonce << "\n";
        outFile << "Sudėtingumas: " << difficulty << "\n";
        outFile << "----------------------------------------\n";
        outFile.close();
        
        std::cout << "Blokas sekmingai irasytas i faila 'block.txt'.\n";
    }
}
