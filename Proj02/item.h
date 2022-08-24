#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <string>

bool itemInit();
void itemQuit();

class item
{
public:
	item();
	virtual ~item();

	bool loadImage(std::string filename);

	void draw(SDL_Surface * dest);

private:
	SDL_Surface * image;
	SDL_Rect pos;
};
