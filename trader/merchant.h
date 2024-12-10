#ifndef MERCHANT_H
#define MERCHANT_H

#include <string>
#include <map>
#include "good.h"

// Merchant superclass
class Merchant {
public:
    std::string name;
    std::map<std::string, Good> inventory; // On-hand inventory
    int purse; // Available funds

    // Constructor
    Merchant(std::string merchantName, int initialFunds);

    // Used for in-trade viewing
    virtual void displayGoods();

    // Used for quick checking
    virtual void checkGoods();

    // Method to add goods to the inventory
    void addGood(const std::string& itemName, int price, int quantity);

    // Buy goods from the merchant
    bool buyGoods(Merchant& buyer, Merchant& seller, const std::string& goodName, int quantity);


    // Sell goods to the merchant
    bool sellGoods(Merchant& seller, Merchant& buyer, const std::string& goodName, int quantity);


    std::string getName();
};

#endif // MERCHANT_H