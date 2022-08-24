#pragma once

#include "item.h"

// Basic text output
class Label : public Item
{
public:
	Label(SDL_Renderer* rend, TTF_Font* fnt, std::string text, int x, int y);

	bool setFont(TTF_Font* fnt);

	void setText(std::string txt);

	TTF_Font* getFont();

	bool buildImage();

	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

private:
	TTF_Font* font;
	SDL_Color textColor;

	std::string words;
	Item bkg;
};
