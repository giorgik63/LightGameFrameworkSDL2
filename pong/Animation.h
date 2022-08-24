#pragma once

#include "item.h"

class animation : public item
{
public:
	animation();
	virtual ~animation();

	bool addImage(std::string filePath);
	bool loadAnimation(std::string pref, std::string zbuf, std::string ext);

	void next();
	void freeImages();
	void setFPS(int FPS);

	virtual void update(int tick);

protected:
	int frameCount;

	std::vector <SDL_Texture*> images;

	int desiredDelta;
};
