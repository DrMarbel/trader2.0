#ifndef PLAYER_H
#define PLAYER_H

#include "merchant.h"

class Player : public Merchant {
public:
    Player(std::string playerName, int initialFunds = 20);
};

#endif