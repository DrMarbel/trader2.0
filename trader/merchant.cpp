#include <string>
#include <map>
#include <iostream>
#include "merchant.h"
#include "good.h"

// Constructor
Merchant::Merchant(std::string merchantName, int initialFunds)
    : name(merchantName), purse(initialFunds) {}

// Used for in-trade viewing
void Merchant::displayGoods() {
    std::cout << "\n--- Goods Available for Trade (Merchant: " << name << ") ---\n";
    for (const auto& pair : inventory) {
        std::cout << pair.second.name << " | Value: " << pair.second.baseValue << " Crowns"
            << " | Available: " << pair.second.quantity << "\n";
    }
    std::cout << "Available Funds: " << purse << " Crowns\n";
}

// Used for quick checking
void Merchant::checkGoods() {
    std::cout << "\n--- Goods Available for Trade (Merchant: " << name << ") ---\n";
    for (const auto& pair : inventory) {
        std::cout << pair.second.name << " | Value: " << pair.second.baseValue << " Crowns"
            << " | Available: " << pair.second.quantity << "\n";
    }
    std::cout << "Available Funds: " << purse << " Crowns\n";

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Method to add goods to the inventory
void Merchant::addGood(const std::string& itemName, int price, int quantity) {
    inventory[itemName] = Good(itemName, price, quantity); // Directly creating Good object
}

// Buy goods from the merchant
bool Merchant::buyGoods(Merchant& buyer, Merchant& seller, const std::string& goodName, int quantity) {
    // Check if the seller has the good
    if (seller.inventory.find(goodName) != seller.inventory.end()) {
        Good& good = seller.inventory[goodName];
        int totalCost = good.baseValue * quantity;

        // Ensure enough stock and buyer's funds
        if (good.quantity >= quantity && buyer.purse >= totalCost) {
            // Update seller's stock
            good.quantity -= quantity;

            // Update buyer's inventory
            if (buyer.inventory.find(goodName) != buyer.inventory.end()) {
                // If the buyer already has the item, increase the quantity
                buyer.inventory[goodName].quantity += quantity;
            }
            else {
                // If the buyer doesn't have the item, add it to inventory
                buyer.inventory[goodName] = Good(goodName, good.baseValue, quantity);
            }

            // Update purses
            seller.purse += totalCost;
            buyer.purse -= totalCost;

            std::cout << "Transaction successful! Bought " << quantity << " " << goodName << "(s).\n";
            return true;
        }
        else {
            std::cout << "Not enough stock or funds to buy " << quantity << " " << goodName << "(s).\n";
            return false;
        }
    }
    else {
        std::cout << "This merchant doesn't sell " << goodName << ".\n";
        return false;
    }
}

// Sell goods to the merchant
bool Merchant::sellGoods(Merchant& seller, Merchant& buyer, const std::string& goodName, int quantity) {
    // Check if the seller (player) has the good
    if (seller.inventory.find(goodName) != seller.inventory.end()) {
        Good& good = seller.inventory[goodName];

        // Check if the player has enough quantity to sell
        if (good.quantity >= quantity) {
            int totalValue = good.baseValue * quantity;

            // Check if the buyer (merchant) has enough money
            if (buyer.purse >= totalValue) {
                // Decrease the seller's stock
                good.quantity -= quantity;

                // If quantity drops to 0, remove the item from the seller's inventory
                if (good.quantity == 0) {
                    seller.inventory.erase(goodName);
                }

                // Add the goods to the buyer's inventory
                if (buyer.inventory.find(goodName) != buyer.inventory.end()) {
                    // If the buyer already has the item, increase its quantity
                    buyer.inventory[goodName].quantity += quantity;
                }
                else {
                    // If the buyer doesn't have the item, add it
                    buyer.inventory[goodName] = Good(goodName, good.baseValue, quantity);
                }

                // Update purses
                seller.purse += totalValue;
                buyer.purse -= totalValue;

                std::cout << "Transaction successful! Sold " << quantity << " " << goodName << "(s) for "
                    << totalValue << " Crowns.\n";
                return true;
            }
            else {
                std::cout << "The buyer doesn't have enough funds to purchase " << quantity
                    << " " << goodName << "(s).\n";
                return false;
            }
        }
        else {
            std::cout << "You don't have enough " << goodName << " to sell.\n";
            return false;
        }
    }
    else {
        std::cout << "You don't have " << goodName << " in your inventory.\n";
        return false;
    }
}

// Return the name of the merchant
std::string Merchant::getName() {
    return name;
}