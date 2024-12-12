#ifndef GOOD_H
#define GOOD_H

#include <string>
#include <vector>

struct Good {
    std::string name;
    int baseValue;
    int quantity;
    std::string rarity;
    std::vector<std::string> availableInRegions;

    Good() : name(""), baseValue(0), quantity(0), rarity("") {}
    Good(std::string n, int v, int q) : name(n), baseValue(v), quantity(q) {}
    Good(std::string n, int v, int q, std::string r) : name(n), baseValue(v), quantity(q), rarity(r) {}
    Good(std::string n, int v, int q, std::string r, std::vector<std::string> regions) : name(n), baseValue(v), quantity(q), rarity(r), availableInRegions(regions) {}
};

#endif