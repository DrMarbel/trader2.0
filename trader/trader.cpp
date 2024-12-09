/*
* Lead Developer: Dr. Marbel
* Development Studio: Philobyte
* Date Started: 12/07/24
* 
* Notes:
* Added Merchant superclass
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip> // For formatted output

// ----- Structs and Classes -----

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

// Merchant superclass
class Merchant {
public:
    std::string name;
    std::map<std::string, Good> inventory; // On-hand inventory
    int purse; // Available funds

    // Constructor
    Merchant(std::string merchantName, int initialFunds)
        : name(merchantName), purse(initialFunds) {}

    // Used for in-trade viewing
    virtual void displayGoods() {
        std::cout << "\n--- Goods Available for Trade (Merchant: " << name << ") ---\n";
        for (const auto& pair : inventory) {
            std::cout << pair.second.name << " | Value: " << pair.second.baseValue << " Crowns"
                << " | Available: " << pair.second.quantity << "\n";
        }
        std::cout << "Available Funds: " << purse << " Crowns\n";
    }

    // Used for quick checking
    virtual void checkGoods() {
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
    void addGood(const std::string& itemName, int price, int quantity) {
        inventory[itemName] = Good(itemName, price, quantity); // Directly creating Good object
    }

    // Buy goods from the merchant
    bool buyGoods(Merchant& buyer, Merchant& seller, const std::string& goodName, int quantity) {
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
    bool sellGoods(Merchant& seller, Merchant& buyer, const std::string& goodName, int quantity) {
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


    std::string getName() {
        return name;
    }
};

// Player subclass
class Player : public Merchant {
public:
    Player(std::string playerName, int initialFunds = 20) : Merchant(playerName, initialFunds) {}
};

// Trader subclass
class Trader : public Merchant {
public:
    Trader(std::string traderName, int initialFunds = 250) : Merchant(traderName, initialFunds) {}
};

// ----- Game Function -----
void trade(Player& player, Merchant& merchant) {
    int choice = 0;
    std::string selection;

    system("cls || clear");

    while (true) {

        // Display trading options
        std::cout << "You are now trading with " << merchant.getName() << ".\n";
        std::cout << "What would you like to do?\n";
        std::cout << "1. Buy goods\n";
        std::cout << "2. Sell goods\n";
        std::cout << "3. Exit trade\n";
        std::cout << "Enter your choice: ";

        std::cin >> choice;

        // Handle invalid input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
        case 1:
        {
            system("cls || clear");

            int qty;
            std::cout << "\n--- Buying Goods ---\n";
            merchant.displayGoods();
            std::cout << "\nWhat would you like to buy?\n";
            std::cin.ignore();
            std::getline(std::cin, selection);
            std::cout << "\nHow many?\n";
            std::cin >> qty;
            player.buyGoods(player, merchant, selection, qty); // Call buy method
            break;
        }
        case 2:
        {
            system("cls || clear");

            int qty;
            std::cout << "\n--- Selling Goods ---\n";
            player.displayGoods();
            std::cout << "\nWhat would you like to sell?\n";
            std::cin.ignore();
            std::getline(std::cin, selection);
            std::cout << "\nHow many?\n";
            std::cin >> qty;
            player.sellGoods(player, merchant, selection, qty); // Call sell method
            break;
        }
        case 3:
            std::cout << "\nYou exit the trade with " << merchant.getName() << ".\n";
            return;

        default:
            std::cout << "Invalid choice. Please select 1, 2, or 3.\n";
            break;
        }

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}

// ----- Main Function -----
int main()
{
    std::cout << "Welcome to the Fantasy Trade Tycoon!\n";

    // Create player
    std::string playerName;
    std::cout << "Enter your character's name: ";
    std::getline(std::cin, playerName);

    Player player(playerName);
    Trader trader("Merric");

    // Hardcoding items into Merric's inventory
    trader.addGood("Elven Bread", 5, 15);
    trader.addGood("Dwarven Forge Steel", 50, 5);
    trader.addGood("Dragon Scale", 200, 2);
    trader.addGood("Healing Potion", 20, 10);
    trader.addGood("Mana Crystal", 75, 4);
    trader.addGood("Silk of Arachnia", 30, 7);
    trader.addGood("Shadowroot Herb", 10, 12);
    trader.addGood("Griffin Feather", 25, 8);
    trader.addGood("Obsidian Trinket", 60, 3);
    trader.addGood("Phoenix Ash", 500, 1);
    trader.addGood("Isabian Cheese Wheel", 3000, 1);

    // Game Loop
    while (true)
    {
        system("cls || clear");

        std::cout << "\n--- Main Menu ---\n";
        std::cout << "1. View Your Inventory\n";
        std::cout << "2. Trade with Merric\n";
        std::cout << "3. Exit Game\n";

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            player.checkGoods();
            break;
        case 2:
            trade(player, trader);
            break;
        case 3:
            std::cout << "Thanks for playing! Goodbye.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}