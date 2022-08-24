//-------------------------------------------------
//
//   Episodio 13
//
//-------------------------------------------------

#include "SDL.h"
#include "SDL_image.h"

#include "item.h"
#include "Animation.h"

#include <iostream>
#include <ctime>     // srand()
#include <cstdlib>   // srand()
#include <vector>

int main(int argc, char* argv[]) 
{
	srand(time(NULL));

	if (!itemInit())
	{
		std::cout << "Error to init!" << std::endl;
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Light Game Framework Episodio 13", 30, 30, 600, 500, SDL_WINDOW_SHOWN);
	SDL_Renderer* screen = SDL_CreateRenderer(win, -1, 0);

	// le gemme
	std::vector <item*> gems;
	int maxGems = 50;
	for (int i = 0; i < maxGems; i++)
	{
		gems.push_back(new item());
		gems[i]->setRenderer(screen);
		gems[i]->loadImage("resources/crystal.png");
		gems[i]->setPos(rand() % 550, rand() % 450);
		gems[i]->setSize(50, 50);
		gems[i]->setCenter(24, 24, 8);
	}

	// cubo che ruota con cuore
	animation box;
	box.setRenderer(screen);
	box.setSize(50, 50);
	box.setPos(200, 100);
	box.setCenter(25, 25, 12);
	std::string path = "resources/heart/";
	std::string count = "0000";
	std::string ext = ".png";
	for (int i = 0; i < 80; i++)
	{
		count[3] += 1;
		if (count[3] > '9')
		{
			count[2] ++;
			count[3] = '0';
		}
		box.addImage(path + count + ext);
	}

	// il personaggio
	animation bob;
	bob.setRenderer(screen);
	bob.loadAnimation("resources/Hero-Guy-PNG/_Mode-Sword/02-Run/JK_P_Sword__Run_", "000", ".png");
	bob.setPos(30, 30);
	bob.setSize(100, 100);
	bob.setCenter(43, 68, 27);

	int speedx = 0;
	int speedy = 0;

	SDL_SetRenderDrawColor(screen, 30, 180, 20, 255);

	double ang = 0;

	bool boxHidden = false;

	int fps = 60;
	int desiredDelta = 1000 / fps;

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		int startLoop = SDL_GetTicks();

		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;

			case SDL_MOUSEBUTTONUP:
				if (box.isClicked(event.button.x, event.button.y))
				{
					boxHidden = true;
				}
				break;

			// avvio lo spostamento del personaggio
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					speedy = -1;
					break;

				case SDLK_DOWN:
					speedy = 1;
					break;

				case SDLK_RIGHT:
					speedx = 1;
					bob.setFlip(SDL_FLIP_NONE);
					break;

				case SDLK_LEFT:
					speedx = -1;
					bob.setFlip(SDL_FLIP_HORIZONTAL);
					break;
				}
				break;

			// fermo lo spostamento del personaggio
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					speedy = 0;
					break;

				case SDLK_DOWN:
					speedy = 0;
					break;

				case SDLK_RIGHT:
					speedx = 0;
					break;

				case SDLK_LEFT:
					speedx = 0;
					break;
				}
				break;
			}
		}

		bob.move(speedx, speedy);

		SDL_RenderClear(screen);

		// disegna la scatola con cuore
		if (!boxHidden)
		{
			box.draw();
		}
		for (int i = 0; i < maxGems; i++)
		{
			if (bob.getCollision(gems[i]))
			{
				gems.erase(gems.begin() + i);
				maxGems--;
			}
			else
			{
				gems[i]->draw(ang);
			}
		}

		// disegna il personaggio
		bob.draw();
		
		SDL_RenderPresent(screen);

		ang++;

		// sprite successivo per animazione scatola che ruota con cuore
		box.next();

		// sprite successivo per animazione personaggio che corre
		bob.next();

		// tempo che scorre tra uno sprite e l'altro per l'animazione
		int delta = SDL_GetTicks() - startLoop;
		if (delta < desiredDelta)
		{
			SDL_Delay(desiredDelta - delta);
		}
	}

	SDL_DestroyWindow(win);

	itemQuit();

	return 0;
}
