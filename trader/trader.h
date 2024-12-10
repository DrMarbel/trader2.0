#include "merchant.h"

// Trader subclass
class Trader : public Merchant {
public:
    Trader(std::string traderName, int initialFunds = 250);
};
