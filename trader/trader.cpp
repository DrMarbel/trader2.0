/*
* Lead Developer: Dr. Marbel
* Development Studio: Philobyte
* Date Started: 12/07/24
* 
* Notes:
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
    std::string rarity;

    // Default constructor
    Good() : name(""), baseValue(0), rarity("Common") {}

    // Parameterized constructor
    Good(std::string n, int v, std::string r) : name(n), baseValue(v), rarity(r) {}
};

// Represents the player
class Player {
public:
    std::string name;
    int currency; // Amount of Crowns the player has
    std::map<std::string, int> inventory; // Good name -> Quantity

    Player(std::string playerName) : name(playerName), currency(20) {} // Start with 20 Crowns

    // Display player's current inventory
    void displayInventory() {
        std::cout << "\n--- " << name << "'s Inventory ---\n";
        std::cout << "Currency: " << currency << " Crowns\n";
        if (inventory.empty()) {
            std::cout << "No goods in inventory.\n";
        }
        else {
            for (const auto& item : inventory) {
                std::cout << item.first << ": " << item.second << "\n";
            }
        }
    }

    // Add goods to inventory
    void addGoods(const std::string& goodName, int quantity) {
        inventory[goodName] += quantity;
    }

    // Remove goods from inventory
    bool removeGoods(const std::string& goodName, int quantity) {
        if (inventory[goodName] < quantity) {
            return false; // Not enough goods
        }
        inventory[goodName] -= quantity;
        if (inventory[goodName] == 0) {
            inventory.erase(goodName); // Clean up empty slots
        }
        return true;
    }
};

// Represents the trader
class Trader {
public:
    std::string name;
    std::map<std::string, Good> goodsForSale;

    Trader(std::string traderName) : name(traderName) {
        // Initialize trader's goods
        goodsForSale["Grain"] = Good("Grain", 2, "Common");
        goodsForSale["Timber"] = Good("Timber", 5, "Common");
        goodsForSale["Salt"] = Good("Salt", 12, "Uncommon");
        goodsForSale["Spices"] = Good("Spices", 30, "Rare");
        goodsForSale["Gems"] = Good("Gems", 75, "Very Rare");
    }

    // Display goods for sale
    void displayGoods() {
        std::cout << "\n--- Goods Available for Trade (Trader: " << name << ") ---\n";
        for (const auto& pair : goodsForSale) {
            std::cout << std::setw(10) << pair.second.name
                << " | Base Value: " << pair.second.baseValue << " Crowns"
                << " | Rarity: " << pair.second.rarity << "\n";
        }
    }
};

// ----- Game Functions -----

void trade(Player& player, Trader& trader) {
    std::string choice;
    int quantity;

    while (true) {
        trader.displayGoods();
        player.displayInventory();

        std::cout << "\nEnter the name of the good you want to buy (or 'exit' to leave): ";
        std::cin >> choice;

        if (choice == "exit") {
            break;
        }

        // Check if the good exists
        if (trader.goodsForSale.find(choice) != trader.goodsForSale.end()) {
            std::cout << "Enter quantity to buy: ";
            std::cin >> quantity;

            int totalCost = trader.goodsForSale[choice].baseValue * quantity;
            if (player.currency >= totalCost) {
                player.currency -= totalCost;
                player.addGoods(choice, quantity);
                std::cout << "You bought " << quantity << " " << choice << "(s) for "
                    << totalCost << " Crowns.\n";
            }
            else {
                std::cout << "Not enough Crowns to complete the purchase.\n";
            }
        }
        else {
            std::cout << "Invalid good. Please choose from the list.\n";
        }
    }
}

// ----- Main Function -----

int main() {
    std::cout << "Welcome to the Fantasy Trade Tycoon!\n";

    // Create player
    std::string playerName;
    std::cout << "Enter your character's name: ";
    std::getline(std::cin, playerName);

    Player player(playerName);
    Trader trader("Merric the Shrewd");

    // Game Loop
    while (true) {
        std::cout << "\n--- Main Menu ---\n";
        std::cout << "1. View Trader's Goods\n";
        std::cout << "2. View Your Inventory\n";
        std::cout << "3. Trade with Merric\n";
        std::cout << "4. Exit Game\n";

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            trader.displayGoods();
            break;
        case 2:
            player.displayInventory();
            break;
        case 3:
            trade(player, trader);
            break;
        case 4:
            std::cout << "Thanks for playing! Goodbye.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}