#include "merchant.h"

// Player subclass
class Player : public Merchant {
public:
    Player(std::string playerName, int initialFunds = 20);
};