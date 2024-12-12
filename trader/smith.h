#pragma once
#include "merchant.h"

// Smith supercubclass
class Smith : public Merchant
{
	// Method to repair damaged goods
	void repair(Good good, Merchant& client);

	// Method to improve lesser quality goods
	void improve(Good good, Merchant& client);

	// Method to crate new items
	void craft(Good ingredientA, Good ingredientB, Merchant& client);
};

