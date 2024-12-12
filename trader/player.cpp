#include <string>
#include <vector> // Include for std::vector
#include "player.h"

Player::Player(std::string playerName, int initialFunds) :
    Merchant(playerName, initialFunds, { "All Regions" }, "Player") {} // Corrected