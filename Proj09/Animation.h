#pragma once

#include "item.h"

class animation : public item
{
public:
	animation();

	bool addImage(std::string filePath);
	void next();

protected:
	int frameCount;
	std::vector <SDL_Texture*> images;
};
