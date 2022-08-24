//-------------------------------------------------
//
//   Episodio 03
//
//-------------------------------------------------

#include "SDL.h"
#include "SDL_image.h"

#include "item.h"

#include <iostream>

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	SDL_Window* win = SDL_CreateWindow("Light Game Framework Episodio 01", 30, 30, 600, 500, SDL_WINDOW_SHOWN);
	SDL_Surface* screen = SDL_GetWindowSurface(win);

	item bob;

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		SDL_FillRect(screen, NULL, 0x00aaff);

		bob.draw(screen);

		SDL_UpdateWindowSurface(win);
	}

	SDL_DestroyWindow(win);

	SDL_Quit();

	return 0;
}