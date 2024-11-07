#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>
#include <cctype> // Būtina, kad veiktų isalpha ir isupper funkcijos

// Funkcija, kuri konvertuoja simbolių eilutę į ASCII kodus
std::string stringToASCII(const std::string& input) {
    std::stringstream asciiStream;
    for (char c : input) {
        asciiStream << std::setw(2) << std::setfill('0') << std::hex << (int)c;
    }
    return asciiStream.str();
}

std::string modifyString(const std::string& input) {
    std::string modified = input;
    for (size_t i = 0; i < modified.length(); i++) {
        char& c = modified[i];
        if (isalpha(c)) {
            int base = (isupper(c)) ? 'A' : 'a';
            int alphabeticPosition = c - base;
            int shift = (alphabeticPosition + (i + 1)) % 26;  // Pakeičiame pagal poziciją
            c = base + shift;
        }
    }
    return modified;
}


// Funkcija, kuri sumažina kiekvieną skaitmenį iki vieno skaitmens po daugybos
// Funkcija, kuri sumažina kiekvieną skaitmenį iki vieno skaitmens po daugybos
int reduceToOneDigit(int num) {
    if (num == 0) return 0; // Jei nulis, grąžina nuli
    int product = 1;
    while (num > 0) {
        product *= num % 10;
        num /= 10;
    }
    // Suskaidome į vieną skaitmenį
    while (product >= 10) {
        int sum = 0;
        while (product > 0) {
            sum += product % 10;
            product /= 10;
        }
        product = sum;
    }
    return product;
}


// Funkcija, kuri apdoroja simbolius, jei ilgis > 64
std::string processLongerInput(const std::string& input) {
    std::vector<int> results;
    std::string hexResult;
    int chunkSize = input.length() / 32;
    int remainder = input.length() % 32;
    for (int i = 0; i < 32; ++i) {
        int chunkSum = 0;
        int currentChunkSize = (i < remainder) ? (chunkSize + 1) : chunkSize;
        for (int j = 0; j < currentChunkSize; ++j) {
            char c = input[i * chunkSize + j + (i < remainder ? i : remainder)];
            int asciiValue = static_cast<int>(c);
            chunkSum += reduceToOneDigit(asciiValue);
        }
        std::stringstream ss;
        ss << std::hex << chunkSum;
        hexResult += ss.str();
    }
    if (hexResult.length() > 64) {
        hexResult = hexResult.substr(0, 64);
    }
    return hexResult;
}

// Maišos funkcija, kuri sugeneruoja 64 simbolių ilgumo maišos kodą
std::string generateHash(const std::string& input) {
    auto start = std::chrono::high_resolution_clock::now();
    std::string hash;
    if (input.length() <= 64) {
        std::string asciiHash = stringToASCII(input);
        int attempt = 0;
        const int maxAttempts = 100;
        while (asciiHash.length() < 64 && attempt < maxAttempts) {
            std::string modifiedInput = modifyString(asciiHash);
            asciiHash += stringToASCII(modifiedInput);
            attempt++;
        }
        if (asciiHash.length() > 64) {
            asciiHash = asciiHash.substr(0, 64);
        }
        hash = asciiHash;
    } else {
        hash = processLongerInput(input);
    }
    if (hash.length() < 64) {
        while (hash.length() < 64) {
            hash += "0";
        }
    } else if (hash.length() > 64) {
        hash = hash.substr(0, 64);
    }
    auto end = std::chrono::high_resolution_clock::now();
    return hash;
}
