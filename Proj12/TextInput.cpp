#include "TextInput.h"

TextInput::TextInput(SDL_Renderer* rend)
{
}

Label TextInput::txt(SDL_Renderer* rend, TTF_Font* fnt, std::string text, int x, int y)
{
	return Label(rend, fnt, text, x, y);
}
