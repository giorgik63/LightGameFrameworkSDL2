#pragma once

#include "item.h"

#include <vector>

class Group : public Item
{
public:
	void draw();
	void addRef(Item* other);

	std::vector<Item*> items;
};
