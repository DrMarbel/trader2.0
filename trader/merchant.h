#ifndef MERCHANT_H
#define MERCHANT_H

#include <string>
#include <map>
#include <vector>
#include "good.h"
#include <algorithm>

class Merchant {
public:
    std::string name;
    std::map<std::string, Good> inventory;
    int purse;
    std::vector<std::string> tradeRegions;
    std::string profession;

    Merchant(std::string merchantName, int initialFunds, std::vector<std::string> regions, std::string prof);

    virtual ~Merchant() = default;

    virtual void displayGoods();
    virtual void checkGoods();
    void addGood(const Good& good, int quantity); // Takes a Good object
    bool buyGoods(Merchant& buyer, Merchant& seller, const std::string& goodName, int quantity);
    bool sellGoods(Merchant& seller, Merchant& buyer, const std::string& goodName, int quantity);
    std::string getName();

    bool isRegionValid(const std::string& region) const; // const is important
};

// Declaration of getAvailableGoods (NOT the definition!)
std::vector<Good> getAvailableGoods(const Merchant& merchant, const std::vector<Good>& allGoods);

#endif // MERCHANT_H