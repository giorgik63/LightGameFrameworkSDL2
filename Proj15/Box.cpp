#include "Box.h"

Box::Box(SDL_Renderer* rend, int x, int y, int w, int h)
{
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = -h;

	ren = rend;

	rbox = 20;
	gbox = 30;
	bbox = 200;
	abox = 255;
}

void Box::draw()
{
	Uint8 r, g, b, a;

	int getter = SDL_GetRenderDrawColor(ren, &r, &g, &b, &a);

	SDL_SetRenderDrawColor(ren, rbox, gbox, bbox, abox);
	SDL_RenderFillRect(ren, &pos);
	if (!getter)
	{
		SDL_SetRenderDrawColor(ren, r, g, b, a);
	}
}

void Box::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	rbox = r;
	gbox = g;
	bbox = b;
	abox = a;
}
