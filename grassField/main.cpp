//-------------------------------------------------
//
//   Demo: expandingWindow
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

	SDL_Window* win = SDL_CreateWindow("Light Game Framework Demo: grassField", 10, 10, 300, 300, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer* screen = SDL_CreateRenderer(win, -1, 0);

	item bkg;
	bkg.setRenderer(screen);
	bkg.loadImage("resources/zoom.png");
	bkg.setSize(300, 300);
	bkg.setPos(0, 0);

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;

			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					// The new size is stored in ev.window, you could also use
					// SDL_GetWindowSize(&x, &y); to fetch the variables
					bkg.setSize(event.window.data1, event.window.data2);
				}
				break;
			}
		}

		SDL_RenderClear(screen);

		bkg.draw();

		SDL_RenderPresent(screen);

		SDL_Delay(30);
	}

	SDL_DestroyWindow(win);

	itemQuit();

	return 0;
}
