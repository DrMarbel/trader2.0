#include <string>
#include <vector> // Very important: Include for std::vector!
#include "trader.h"

Trader::Trader(std::string traderName, int initialFunds) :
    Merchant(traderName, initialFunds, { "Temperate", "Grasslands", "Farmlands" }, "Trader") {}