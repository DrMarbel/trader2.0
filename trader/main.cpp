/*
* Lead Developer: Dr. Marbel
* Development Studio: Philobyte
* Date Started: 12/07/24
* 
* Notes:
* 
*/

#include <iostream>
#include <string>
#include <vector>
#include "merchant.h"
#include "good.h"
#include "player.h"
#include "trader.h"
#include "fstream"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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

std::vector<Good> loadGoodsFromJson(const std::string& filename) {
    std::vector<Good> goods;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return goods; // Return empty vector on error
    }

    try {
        json data = json::parse(file);

        for (const auto& item : data["Inventory"]) {
            std::string name = item["name"];
            int baseValue = item["baseValue"];
            std::string rarity = item["rarity"];

            std::vector<std::string> regions;
            for (const auto& region : item["regionCategories"]) {
                regions.push_back(region);
            }

            goods.emplace_back(name, baseValue, 0, rarity, regions);
        }
    }
    catch (const json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
    catch (const json::type_error& e) {
        std::cerr << "JSON type error: " << e.what() << std::endl;
    }

    return goods;
}

int main() {
    std::cout << "Welcome to the Fantasy Trade Tycoon!\n";

    std::vector<Good> loadedGoods = loadGoodsFromJson("goods.json");

    if (loadedGoods.empty()) {
        std::cerr << "Failed to load goods. Exiting.\n";
        return 1;
    }

    std::string playerName;
    std::cout << "Enter your character's name: ";
    std::getline(std::cin, playerName);

    Player player(playerName);

    Trader merric("Merric", 250);

    std::vector<Good> availableToMerric = getAvailableGoods(merric, loadedGoods);

    for (const auto& good : availableToMerric) {
        merric.addGood(good, 5);
    }

    merric.displayGoods();

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
            trade(player, merric);
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