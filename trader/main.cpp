/*
* Lead Developer: Dr. Marbel
* Development Studio: Philobyte
* Date Started: 12/07/24
* 
* Notes:
* Can Trade with Merric
* Started a dynamic inventory system
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip> // For formatted output

// ----- Structs and Classes -----
#include "merchant.h"
#include "good.h"
#include "player.h"
#include "trader.h"

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