#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono> 

// Funkcija, kuri konvertuoja simbolių eilutę į ASCII kodus
std::string stringToASCII(const std::string& input) {
    std::stringstream asciiStream;

    for (char c : input) {
        // Konvertuojame kiekvieną simbolį į jo ASCII reikšmę ir paverčiame į hex formatą
        asciiStream << std::setw(2) << std::setfill('0') << std::hex << (int)c;
    }

    std::string result = asciiStream.str();
    return result;
}

std::string modifyString(const std::string& input) {
    std::string modified = input;

    for (size_t i = 0; i < modified.length(); i++) {
        char& c = modified[i];
        if (isalpha(c)) {
            // Nustatome, kurioje vietoje abėcėlėje yra simbolis (pradedame nuo 'A' arba 'a')
            int base = isupper(c) ? 'A' : 'a';
            int alphabeticPosition = c - base; // nustatome simbolio poziciją abėcėlėje

            int shift = (alphabeticPosition + (i + 1)) % 26; // apskaičiuojame perkėlimą
            c = base + shift; // perkeliamas į naują vietą pagal abėcėlės pradžią
        }
    }

    return modified;
}

// Funkcija, kuri sumažina kiekvieną skaitmenį iki vieno skaitmens po daugybos
int reduceToOneDigit(int num) {
    if (num == 0) return 0; // Pridėta sąlyga, kad nenukristų į 0

    int product = 1, sum = 0;

    // Sudauginame skaitmenis
    while (num > 0) {
        int digit = num % 10;
        product *= digit;
        num /= 10;
    }

    // Sudedame daugybos rezultatą
    while (product > 0) {
        sum += product % 10;
        product /= 10;
    }

    // Jei suma daugiau nei vienženklis, tęsiame procesą
    return (sum > 9) ? reduceToOneDigit(sum) : sum;
}

// Funkcija, kuri apdoroja simbolius, jei ilgis > 64
std::string processLongerInput(const std::string& input) {
    std::vector<int> results;
    std::string hexResult;

    // Padaliname į 32 dalis
    int chunkSize = input.length() / 32;
    int remainder = input.length() % 32; // Liekančių simbolių

    for (int i = 0; i < 32; ++i) {
        int chunkSum = 0;
        int currentChunkSize = (i < remainder) ? (chunkSize + 1) : chunkSize; // Paskirstome liekančius simbolius

        // Kiekvieną dalį verčiame į ASCII ir atliekame operacijas
        for (int j = 0; j < currentChunkSize; ++j) {
            char c = input[i * chunkSize + j + (i < remainder ? i : remainder)];
            int asciiValue = static_cast<int>(c);
            chunkSum += reduceToOneDigit(asciiValue); // Sumažiname iki vieno skaitmens
        }

        // Kiekvieną sumažintą reikšmę konvertuojame į hex formatą
        std::stringstream ss;
        ss << std::hex << chunkSum;
        hexResult += ss.str();
    }

    // Apkarpome iki 64 simbolių
    if (hexResult.length() > 64) {
        hexResult = hexResult.substr(0, 64);
    }

    return hexResult;
}

// Maišos funkcija, kuri sugeneruoja 64 simbolių ilgumo maišos kodą
std::string generateHash(const std::string& input) {
    auto start = std::chrono::high_resolution_clock::now(); // Pradėti matuoti laiką

    std::string hash;
    if (input.length() <= 64) {
        std::string asciiHash = stringToASCII(input);

        int attempt = 0;
        const int maxAttempts = 100; // Maksimalus bandymų skaičius

        while (asciiHash.length() < 64 && attempt < maxAttempts) {
            std::string modifiedInput = modifyString(asciiHash);  // Naudojame jau sugeneruotą ASCII kaip įvestį
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
            hash += "0"; // Galite pasirinkti kitus simbolius, jei norite
        }
    } else if (hash.length() > 64) {
        hash = hash.substr(0, 64);
    }

    auto end = std::chrono::high_resolution_clock::now(); // Pabaigti matuoti laiką
   // std::chrono::duration<double, std::milli> elapsed = end - start; // Laikas milisekundėmis

    return hash;
}
