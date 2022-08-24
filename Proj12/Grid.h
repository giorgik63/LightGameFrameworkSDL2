#pragma once

#include "item.h"

class Grid : public Item
{

public:
	Grid(SDL_Renderer* rend, int tx, int ty);

	void fill(Item* brush);

	// use stamp for static background images 
	void stamp(Item* brush, int px, int py);

	// use set for animations, collision, and interactive tiles
	void set(Item* tile, int tx, int ty);

private:
	std::vector <std::vector <Item*> > tiles;
};
