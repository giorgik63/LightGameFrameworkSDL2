//-------------------------------------------------
//
//   Episodio 04
//
//-------------------------------------------------

#include "SDL.h"
#include "SDL_image.h"

#include "item.h"

#include <iostream>
#include <ctime>     // srand()
#include <cstdlib>

int main(int argc, char* argv[]) 
{
	srand(time(NULL));

	if (!itemInit())
	{
		std::cout << "Error to init!" << std::endl;
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Light Game Framework Episodio 04", 30, 30, 600, 500, SDL_WINDOW_SHOWN);
	SDL_Surface* screen = SDL_GetWindowSurface(win);

	item bob;
	bob.loadImage("resources/grass.png");

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

	itemQuit();

	return 0;
}
