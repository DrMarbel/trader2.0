#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <vector>
#include "region.h"
#include "good.h"

class GameWorld {
public:
	// Default constructor
	GameWorld() = default;

	// Virtual destructor
	virtual ~GameWorld() = default;
private:
	std::vector<Region> regions;
	std::vector<Good> goods;
};

#endif