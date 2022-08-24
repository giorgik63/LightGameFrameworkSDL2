#include "Label.h"

Label::Label(SDL_Renderer* rend, TTF_Font* fnt, std::string text, int x, int y)
{
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	textColor.a = 200;

	ren = rend;
	font = fnt;
	words = text;

	pos.x = x;
	pos.y = y;

	buildImage();
}

bool Label::setFont(TTF_Font* fnt)
{
	return false;
}

TTF_Font* Label::getFont()
{
	return this->font;
}

bool Label::buildImage()
{
	if (font != NULL)
	{
		SDL_Surface* textSrc = TTF_RenderText_Solid(font, words.c_str(), textColor);

		image = SDL_CreateTextureFromSurface(ren, textSrc);
		pos.w = textSrc->w;
		pos.h = textSrc->h;

		SDL_FreeSurface(textSrc);
	}

	return image != NULL;
}

void Label::setColor(Uint8 r, Uint8 b, Uint8 g, Uint8 a)
{
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;
	textColor.a = a;
}

void Label::setText(std::string txt)
{
	words = txt;
}
