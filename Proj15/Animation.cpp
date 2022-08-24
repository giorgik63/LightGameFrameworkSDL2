#include "Animation.h"

#include <iostream>

animation::animation()
{

}

animation::~animation()
{
	this->freeImages();
}

bool animation::addImage(std::string filePath)
{
	if (loadImage(filePath))
	{
		images.push_back(image);
		return true;
	}

	return false;
}

bool animation::loadAnimation(std::string p, std::string zb, std::string ext)
{
	int leng = zb.length() - 1;

	while (addImage(p + zb + ext) && zb[0] < '9')
	{
		zb[leng] ++;

		for (int i = leng; i >= 0; i--)
		{
			if (zb[i] > '9')
			{
				zb[i - 1]++;
				zb[i] = '0';
			}
		}
	}
	if (!(images.empty()))
	{
		return true;
	}
	else
	{
		image = NULL;
		std::cout << "Failed to load Animation: " << p << std::endl;
	}

	return false;
}

void animation::next()
{
	if (images.empty())
	{
		std::cout << "Tried to update an empty Animation" << std::endl;
	}
	else
	{
		frameCount++;
		image = images[frameCount % (images.size() - 1)];
	}
}

void animation::freeImages()
{
	for (int i = 0; i < images.size(); i++)
	{
		if (images[i] != NULL)
		{
			SDL_DestroyTexture(images[i]);
			images[i] = NULL;
		}
	}
}

void animation::setFPS(int FPS)
{
	desiredDelta = 1000 / FPS;
}

void animation::setFlip(SDL_RendererFlip flip)
{
	Item::flip = flip;
}

void animation::update(int tick)
{
	if (tick - oldTick > desiredDelta)
	{
		next();
		oldTick = tick;
	}
}
