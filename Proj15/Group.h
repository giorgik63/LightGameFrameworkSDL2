#pragma once

#include "item.h"

#include <vector>

class Group : public Item
{
public:
	void draw();
	void addRef(Item* other);
	void move(int x, int y);

	std::vector<Item*> items;
};
