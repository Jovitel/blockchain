#ifndef USER_H
#define USER_H

#include <string>
#include <vector> // Pridėkite šį įrašą

struct User {
    std::string name;
    std::string publicKey;
    double balance;
};

std::vector<User> generateUsersList(int numberOfUsers);
std::string generateUniqueHash(const std::string& userName, int userID, double balance);

#endif // USER_H
