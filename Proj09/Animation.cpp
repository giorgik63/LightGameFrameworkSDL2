#include "Animation.h"

animation::animation()
{

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

void animation::next()
{
	frameCount++;
	image = images[frameCount % (images.size() - 1)];
}
