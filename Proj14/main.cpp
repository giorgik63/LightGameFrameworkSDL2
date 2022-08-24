//-------------------------------------------------
//
//   Episodio 19
//
//-------------------------------------------------

#include "SDL.h"
#include "SDL_image.h"

#include "item.h"
#include "Animation.h"
#include "Group.h"

#include <iostream>
#include <ctime>     // srand()
#include <cstdlib>   // srand()
#include <vector>

int main(int argc, char* argv[]) 
{
	srand(time(NULL));

	Item item;

	SDL_Window* win = SDL_CreateWindow("Light Game Framework Episodio 19", 30, 30, 600, 500, SDL_WINDOW_SHOWN);
	SDL_Renderer* screen = SDL_CreateRenderer(win, -1, 0);

	Group drawn;

	// le gemme
	std::vector <Item*> gems;
	int maxGems = 50;
	for (int i = 0; i < maxGems; i++)
	{
		gems.push_back(new Item());
		gems[i]->setRenderer(screen);
		gems[i]->loadImage("resources/crystal.png");
		gems[i]->setPos(rand() % 550, rand() % 450);
		gems[i]->setSize(50, 50);
		gems[i]->setCenter(24, 24, 8);

		drawn.addRef(gems[i]);
	}

	// cubo che ruota con cuore
	animation box;
	box.setFPS(18);
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
	bob.setFPS(15);
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

	// carica la musica di sottofondo
	Mix_Music* music = Mix_LoadMUS("resources/RPGAmbient.mp3");
	Mix_PlayMusic(music, 0);

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

				case SDLK_SPACE:
					if (Mix_PausedMusic())
					{
						Mix_ResumeMusic();
					}
					else
					{
						Mix_PauseMusic();
					}
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

		// sposta il personaggio secondo i tasti freccia <-, ->, sù, giù
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
			//else
			//{
			//	gems[i]->draw(ang);
			//}
		}

		// disegna le gemme
		drawn.draw();

		// disegna il personaggio
		bob.draw();
		
		SDL_RenderPresent(screen);

		ang++;

		// sprite successivo per animazione scatola che ruota con cuore
		//box.next();
		box.update(startLoop);

		// sprite successivo per animazione personaggio che corre
		//bob.next();
		bob.update(startLoop);

		// tempo che scorre tra uno sprite e l'altro per l'animazione
		int delta = SDL_GetTicks() - startLoop;
		if (delta < desiredDelta)
		{
			SDL_Delay(desiredDelta - delta);
		}
	}

	Mix_HaltMusic();

	SDL_DestroyWindow(win);

	return 0;
}
