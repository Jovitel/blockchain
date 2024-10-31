#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string name;
    std::string publicKey;
    double balance;

    // Konstruktorius
    User(const std::string& name, const std::string& publicKey, double balance);

    // Funkcija balanso atnaujinimui
    void updateBalance(double amount);
};

#endif // USER_H
