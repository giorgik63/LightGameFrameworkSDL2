//-------------------------------------------------
//
//   Demo: pong
//
//-------------------------------------------------
// A simple pong-like game and proof of concept.
// To Do:
// 	Flip animation for both ninjaGirl and dragon's direction
// 	Fix 'dragon grab'
// 	Allow user to choose characters
// 	Add an attack feature that changes ball's speed/direction
// 	Scoring system

#include "SDL.h"
#include "SDL_image.h"

#include "item.h"
#include "Animation.h"

#include <iostream>

class flipped : public animation
{
public:
	void draw();
};

void flipped::draw()
{
	SDL_RenderCopyEx(ren, image, NULL, &pos, 0, NULL, SDL_FLIP_HORIZONTAL);
}

void saveScreen(const char* file_name, SDL_Renderer* renderer) {
	SDL_Surface* surface = SDL_CreateRGBSurface(0, 2048, 1152, 32, 0, 0, 0, 0);
	SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
	IMG_SavePNG(surface, file_name);
	SDL_FreeSurface(surface);
}

int main(int argc, char* argv[]) 
{
	if (!itemInit())
	{
		std::cout << "Error to init!" << std::endl;
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Light Game Framework Demo: Dragon Pong", 30, 30, 2048, 1152, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer* screen = SDL_CreateRenderer(win, -1, 0);
	SDL_Texture* target = SDL_GetRenderTarget(screen);

	item bkg;
	int x, y;
	SDL_GetWindowSize(win, &x, &y);
	bkg.setRenderer(screen);
	bkg.setSize(x, y);
	bkg.setPos(0, 0);
	bkg.loadImage("battleback1.png");

	animation first;
	first.setRenderer(screen);
	first.setCenter(75, 100, 120);
	first.setSize(150, 240);
	first.setPos(90, 500);
	first.loadAnimation("transparent PNG/run/frame-", "1", ".png");

	flipped second;
	second.setRenderer(screen);
	second.setCenter(75, 100, 120);
	second.setSize(150, 240);
	second.setPos(1520, 450);
	second.loadAnimation("png/Run__", "000", ".png");

	animation ball;
	ball.setRenderer(screen);
	ball.setCenter(75, 75, 25);
	ball.setSize(150, 150);
	ball.setPos(980, 550);
	ball.loadAnimation("PNG/frame-", "1", ".png");

	item net;
	net.setRenderer(screen);
	net.setPos(980, 200);
	net.setSize(50, 700);
	net.loadImage("net.png");

	SDL_SetRenderDrawColor(screen, 30, 180, 20, 255);

	int fps = 10;
	int desiredDelta = 1000 / fps;
	int speedy = 0, speedy2 = 0, speedx = 0, speedx2 = 0;
	int ballSpeedX = -18;
	int ballSpeedY = 15;
	int playerSpeed = 8;

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

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					speedy2 = -playerSpeed;
					break;

				case SDLK_DOWN:
					speedy2 = playerSpeed;
					break;

				case SDLK_LEFT:
					speedx2 = -playerSpeed;
					break;

				case SDLK_RIGHT:
					speedx2 = playerSpeed;
					break;

				case SDLK_w:
					speedy = -playerSpeed;
					break;

				case SDLK_s:
					speedy = playerSpeed;
					break;

				case SDLK_a:
					speedx = -playerSpeed;
					break;

				case SDLK_d:
					speedx = playerSpeed;
					break;
				}
				break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
				case SDLK_DOWN:
					speedy2 = 0;
					break;

				case SDLK_LEFT:
				case SDLK_RIGHT:
					speedx2 = 0;
					break;

				case SDLK_w:
				case SDLK_s:
					speedy = 0;
					break;

				case SDLK_a:
				case SDLK_d:
					speedx = 0;
					break;
				}
				break;

			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					x = event.window.data1;
					y = event.window.data2;
					bkg.setSize(x, y);
					second.setPos(x - (2 * second.getPos()->w), second.getPos()->y);
				}
				break;
			}
		}

		first.move(speedx, speedy);
		second.move(speedx2, speedy2);
		ball.move(ballSpeedX, ballSpeedY);

		bkg.draw();
		net.draw();
		first.draw();
		second.draw();
		ball.draw();

		SDL_RenderPresent(screen);

		if (speedx || speedy)
		{
			first.next();
		}

		if (speedx2 || speedy2)
		{
			second.next();
		}

		ball.next();
		if (first.getCollision(&ball) || second.getCollision(&ball))
		{
			ballSpeedX *= -1;
		}

		if (ball.getPos()->y < 0 || ball.getPos()->y > y - ball.getPos()->h)
		{
			ballSpeedY *= -1;
		}

		if (ball.getPos()->x < 0)
		{
			// second player scores
			ball.setPos(x / 2, y / 2);
			ballSpeedX *= -1;
		}

		if (ball.getPos()->x + ball.getPos()->w > x)
		{
			// second player scores
			ball.setPos(x / 2, y / 2);
			ballSpeedX *= -1;
		}

		if (ball.getPos()->y > y)
		{
			ball.setPos(x / 2, y / 2);
		}

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
