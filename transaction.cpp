#include "transaction.h"
#include <sstream>

Transaction::Transaction(std::string sender, std::string receiver, int amount)
    : senderPublicKey(sender), receiverPublicKey(receiver), amount(amount) {
    std::stringstream ss;
    ss << sender << receiver << amount;
    transactionID = std::to_string(std::hash<std::string>{}(ss.str())); // Laikinas ID generavimas
}

// Print method implementation
void Transaction::printTransaction() const {
    std::cout << "Transakcijos ID: " << transactionID << std::endl;
    std::cout << "Siuntėjo viešasis raktas: " << senderPublicKey << std::endl;
    std::cout << "Gavėjo viešasis raktas: " << receiverPublicKey << std::endl;
    std::cout << "Suma: " << amount << std::endl;
}
