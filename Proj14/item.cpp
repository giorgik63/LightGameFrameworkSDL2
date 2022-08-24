#include "item.h"

#include <iostream>
#include <fstream>

Item::Item()
{
	pos.x = 30;
	pos.y = 60;

	image = NULL;

	pos.w = 100;
	pos.h = 100;

	oldTick = 0;

	itemInit();
}

Item::Item(SDL_Renderer* renderer, std::string loadImg)
{
	this->ren = renderer;
	this->loadImage(loadImg);

	pos.x = 0;
	pos.y = 0;

	SDL_QueryTexture(image, NULL, NULL, &(pos.w), &(pos.h));
}

Item::~Item()
{
	if(image != NULL)
	{
		SDL_DestroyTexture(image);
		image = NULL;
	}

	SDL_Quit();
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDLNet_Quit();
}

Item* Item::getSelf()
{
	return this;
}

void Item::itemInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
	{
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
		return;
	}

	if (!(IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG)))
	{
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
		return;
	}

	flip = SDL_FLIP_NONE;

	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OPUS | MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 4096);

	TTF_Init();
	SDLNet_Init();
}

bool Item::loadImage(std::string filename)
{
	SDL_Surface* temp = IMG_Load(filename.c_str());
	if (temp != NULL)
	{
		image = SDL_CreateTextureFromSurface(ren, temp);
		SDL_FreeSurface(temp);
		if (image != NULL)
		{
			return true;
		}
	}

	return false;
}

void Item::freeImage()
{
	if (image != NULL)
	{
		SDL_DestroyTexture(image);
		image = NULL;
	}
}

void Item::setRenderer(SDL_Renderer* dest)
{
	ren = dest;
}

void Item::setSize(int w, int h)
{
	pos.w = w;
	pos.h = h;
}

void Item::setPos(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

SDL_Rect* Item::getPos()
{
	return &pos;
}

int Item::fileSize(std::string path)
{
	std::ifstream file(path.c_str());
	file.seekg(file.end);

	int val = file.tellg();

	file.close();

	return val;
}

SDL_Texture* Item::getImage()
{
	return image;
}

void Item::move(int x, int y)
{
	pos.x += x;
	pos.y += y;
}

bool Item::getCollision(Item* other)
{
	int dx, dy, rs;
	dx = pos.x + center.x - (other->getPos()->x + other->getCenter().x);
	dy = pos.y + center.y - (other->getPos()->y + other->getCenter().y);
	rs = center.r + other->getCenter().r;
	dx *= dx;
	dy *= dy;
	rs *= rs;
	if (dx + dy < rs)
	{
		return true;
	}

	return false;

}

bool Item::isClicked(int x, int y)
{
	int dx, dy, rs;
	dx = pos.x + center.x - x;
	dy = pos.y + center.y - y;
	rs = center.r;
	dx *= dx;
	dy *= dy;
	rs *= rs;

	return (dx + dy < rs);
}

circle Item::getCenter()
{
	return center;
}

void Item::setCenter(int x, int y, int r)
{
	center.x = x;
	center.y = y;
	center.r = r;
}

void Item::draw(double angle)
{
	if (image != NULL)
	{
		SDL_RenderCopyEx(ren, image, NULL, &pos, angle, NULL, SDL_FLIP_NONE);
	}
	else
	{
		std::cout << "Help, image is NULL at draw()\n";
	}
}

void Item::draw()
{
	if (image != NULL)
	{
		//SDL_RenderCopy(ren, image, NULL, &pos);
		SDL_RenderCopyEx(ren, image, NULL, &pos, 0, NULL, flip);
	}
	else
	{
		std::cout << "Help, image is NULL at draw()\n";
	}
}

void Item::update(int tick)
{
	oldTick = tick;
}

void Item::stamp(Item* paper, int x, int y)
{
}

void Item::preloop()
{
}

bool Item::ready()
{
	return true;
}

void Item::handleEvent(SDL_Event* ev)
{
}

void Item::cleanup()
{
}
