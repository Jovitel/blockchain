#include "user.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // srand, rand
#include <ctime> // time
#include <fstream> // ofstream
#include <functional> // std::hash
#include "hash_function.h"

std::vector<User> generateUsersList(int numberOfUsers) {
    std::vector<User> users;
    srand(static_cast<unsigned>(time(0)));

    const std::vector<std::string> names = {
        "Olivia", "Emma", "Charlotte", "Amelia", "Sophia", "Mia", "Isabella",
        "Ava", "Evelyn", "Luna", "Harper", "Sofia", "Camila", "Eleanor", 
        "Elizabeth", "Violet", "Scarlett", "Emily", "Hazel", "Lily", 
        "Gianna", "Aurora", "Penelope", "Aria", "Nora", "Chloe", "Ellie", 
        "Mila", "Avery", "Layla", "Abigail", "Ella", "Isla", "Eliana", 
        "Nova", "Madison", "Zoe", "Ivy", "Grace", "Lucy", "Willow", 
        "Emilia", "Riley", "Naomi", "Victoria", "Stella", "Elena", 
        "Hannah", "Valentina", "Maya", "Zoey", "Delilah", "Leah", 
        "Lainey", "Lillian", "Paisley", "Genesis", "Madelyn", "Sadie", 
        "Sophie", "Leilani", "Addison", "Natalie", "Josephine", "Alice", 
        "Ruby", "Claire", "Kinsley", "Everly", "Emery", "Adeline", 
        "Kennedy", "Maeve", "Audrey", "Autumn", "Athena", "Eden", 
        "Iris", "Anna", "Eloise", "Jade", "Maria", "Caroline", 
        "Brooklyn", "Quinn", "Aaliyah", "Vivian", "Liliana", "Gabriella", 
        "Hailey", "Sarah", "Savannah", "Cora", "Madeline", "Natalia", 
        "Ariana", "Lydia", "Lyla", "Clara", "Allison"
    };

    // Atidaryti failą rašymui ir išvalyti turinį
    std::ofstream outFile("users.txt", std::ios::trunc); // Naudojame trunc, kad išvalytume failą
    if (!outFile.is_open()) {
        std::cerr << "Klaida atidarant failą rašymui!\n";
        return users;
    }

    for (int i = 0; i < numberOfUsers; ++i) {
        User user;
        user.name = names[i % names.size()] + " " + std::to_string(i + 1);
        
        // Generuojame viešąjį raktą
        std::string rawPublicKey = "PublicKey_" + std::to_string(rand());
        
        // Paverčiame viešąjį raktą į maišos kodą
        user.publicKey = generateHash(user.name);
        
        user.balance = 100 + (rand() % 1000000);

        users.push_back(user);

        // Rašyti informaciją į failą
        outFile << "Vartotojas: " << user.name << "\n";
        outFile << "Viešasis raktas: " << user.publicKey << "\n";
        outFile << "Balansas: " << user.balance << "\n";
    }

    outFile.close(); // Uždarome failą
    std::cout << "Vartotojai sugeneruoti ir irasyti i users.txt faila.\n";

    return users; // Grąžinkite sukurtų vartotojų sąrašą
}
