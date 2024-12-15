#ifndef REGION_H
#define REGION_H

#include <string>
#include <vector>

struct Region {
	std::string name;
	std::string climate;
	std::vector<std::string> resources;
};

#endif