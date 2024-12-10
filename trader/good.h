#ifndef GOOD_H
#define GOOD_H

#include <string>

// Represents a tradeable good
struct Good {
    std::string name;
    int baseValue; // Base value of the good in Crowns
    int quantity;

    // Default constructor
    Good() : name(""), baseValue(0) {}

    // Parameterized constructor
    Good(std::string n, int v, int q) : name(n), baseValue(v), quantity(q) {}
};

#endif // GOOD_H