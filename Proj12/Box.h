#pragma once

#include "item.h"

class Box : public Item
{
public:
	Box(SDL_Renderer* rend, int x, int y, int w, int h);

	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	virtual void draw();

private:
	double max, min, val;

	Uint8 rbox, gbox, bbox, abox;
};
