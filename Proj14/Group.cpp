#include "Group.h"

void Group::draw()
{
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->draw();
	}
}

void Group::addRef(Item* other)
{
	items.push_back(other);
}
