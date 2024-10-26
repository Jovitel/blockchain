#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H

#include <string>

// Funkcijų prototipai
std::string stringToASCII(const std::string& input);
std::string modifyString(const std::string& input);
std::string generateHash(const std::string& input);
std::string processLongerInput(const std::string& input); // Pridėta nauja funkcija
std::string generateHash(const std::string& input);
#endif // HASH_FUNCTION_H
