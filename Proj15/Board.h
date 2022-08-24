#pragma once

#include "item.h"
#include "Group.h"

class Board : public Item
{
public:
	Board(SDL_Renderer* rend);

	void draw();
	void move(int x, int y);

	Item player;
	Item bkg;

	Group drawn;
	Group click;
	Group collide;
};
