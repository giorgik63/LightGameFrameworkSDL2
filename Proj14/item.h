#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_net.h"

#include <string>
#include <vector>

struct circle
{
	int x, y, r;
};

class Item
{
public:
	Item();
	Item(SDL_Renderer* renderer, std::string loadImg);
	virtual ~Item();

	Item* getSelf();

	void itemInit();

	void setRenderer(SDL_Renderer* renderer);

	bool loadImage(std::string filename);

	void freeImage();
	void setSize(int w, int h);
	void setPos(int x, int y);

	int fileSize(std::string path);

	SDL_Rect* getPos();
	SDL_Texture* getImage();

	virtual void move(int x, int y);

	virtual bool getCollision(Item* other);

	virtual bool isClicked(int x, int y);

	virtual circle getCenter();
	virtual void setCenter(int x, int y, int r);

	virtual void draw(double angle);
	virtual void draw();
	virtual void update(int tick);
	virtual void stamp(Item* paper, int x, int y);

	// some virtual functions for plugins
	//
	// take a second to load resources, populate board, etc
	virtual void preloop();
	// Make sure all threads are ready to run before going to user interaction
	virtual bool ready();
	// sent only on event detected 
	virtual void handleEvent(SDL_Event* ev);
	// clean up gracefully before a close. Might be a reset to menu
	// so it should be a clean exit of the plugin.
	virtual void cleanup();

protected:
	SDL_Renderer* ren;
	SDL_Texture* image;
	SDL_Rect pos;
	SDL_RendererFlip flip;

	circle center;

	int oldTick;
};
