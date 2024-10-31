#ifndef VARTOTOJAS_H
#define VARTOTOJAS_H

#include <string>

class Vartotojas {
private:
    std::string vardas;
    std::string viesasis_raktas;
    int balansas;

public:
    Vartotojas() = default;
    Vartotojas(const std::string& vardas, const std::string& viesasis_raktas, int balansas) 
        : vardas(vardas), viesasis_raktas(viesasis_raktas), balansas(balansas) {}

    std::string getVardas() const { return vardas; }
    std::string getViesasisRaktas() const { return viesasis_raktas; }
    int getBalansas() const { return balansas; }
    void setBalansas(int newBalansas) { balansas = newBalansas; }
};

#endif // VARTOTOJAS_H
