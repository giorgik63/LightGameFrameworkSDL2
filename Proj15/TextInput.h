#pragma once

#include "item.h"
#include "Label.h"

class TextInput : public Item
{
public:
	TextInput(SDL_Renderer* rend);

private:
	Label txt(SDL_Renderer* rend, TTF_Font* fnt, std::string text, int x, int y);
	Item bkg, bkgInset, bkgOutset;
};
