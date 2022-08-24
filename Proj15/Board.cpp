#include "Board.h"

Board::Board(SDL_Renderer* rend)
{
	ren = rend;

	int w, h;

	SDL_GetRendererOutputSize(ren, &w, &h);

	player.setPos((w / 2) - 32, (h / 2) - 32);

	bkg.setSize(w, h);
	bkg.setPos(0, 0);
}

void Board::draw()
{
	bkg.draw();

	drawn.draw();

	player.draw();
}

void Board::move(int x, int y)
{
	drawn.move(-x, -y);

	click.move(-x, -y);

	collide.move(-x, -y);
}
