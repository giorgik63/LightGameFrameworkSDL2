#include "BarGraph.h"
#include "Box.h"

BarGraph::BarGraph(SDL_Renderer* rend, int x, int y, int w, int h)
{
	ren = rend;

	image = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;

	rbar = 20;
	gbar = 30;
	bbar = 200;
	abar = 255;

	Uint8 r, g, b, a;

	//	SDL_GetRenderDrawColor(ren, &r, &g, &b, &a);
	SDL_SetRenderTarget(ren, image);
	SDL_SetRenderDrawColor(ren, 130, 180, 255, 255);
	SDL_RenderClear(ren);
	SDL_RenderFillRect(ren, NULL);
	SDL_SetRenderTarget(ren, NULL);
	//	SDL_SetRenderDrawColor(ren, r, g, b, a);

	maxVal = 2;
	minVal = 0;
	sampleCount = 0;
}

void BarGraph::refresh()
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(ren, &r, &g, &b, &a);
	SDL_SetRenderTarget(ren, image);
	SDL_SetRenderDrawColor(ren, 130, 180, 255, 255);
	SDL_RenderClear(ren);

	if (bkg.getImage() != NULL)
	{
		bkg.draw();
	}

	int width = pos.w / value.size();
	int zeroY = maxVal / (maxVal - minVal) * pos.h;

	if (minVal == maxVal)
	{
		maxVal += 1;
	}

	int mx, my;

	SDL_GetMouseState(&mx, &my);

	mx -= pos.x;

	for (int i = 0; i < value.size(); i++)
	{
		//box sq(ren, i * width, pos.h, width - 1, value[i]/(maxVal - minVal)*(pos.h + 5));
		Box sq(ren, i * width, zeroY, width - 1, value[i] / (maxVal - minVal) * (pos.h + 5));

		if (mx > sq.getPos()->x && mx <= sq.getPos()->x + sq.getPos()->w)
		{
			sq.setColor(255, 255, 255, abar);
		}
		else
		{
			sq.setColor(rbar, gbar, bbar, abar);
		}

		sq.draw();
	}

	SDL_SetRenderTarget(ren, NULL);
	SDL_SetRenderDrawColor(ren, r, g, b, a);
}

void BarGraph::addValue(std::string aname, double aval)
{
	if (aval > maxVal)
	{
		maxVal = aval;
	}

	if (aval < minVal)
	{
		minVal = aval;
	}

	name.push_back(aname);
	value.push_back(aval);

	sampleCount++;

}

void BarGraph::setBarColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	rbar = r;
	gbar = g;
	bbar = b;
	abar = a;
}

void BarGraph::setBkgImage(std::string ipath)
{
	bkg.setRenderer(ren);
	bkg.loadImage(ipath);
	bkg.setSize(pos.w, pos.h);
	bkg.setPos(0, 0);

}
std::string BarGraph::getLabel(int index)
{
	if (index < name.size())
	{
		return name[index];
	}

	return "outOfBounds";
}

double BarGraph::getValue(int index)
{
	if (index < value.size())
	{
		return value[index];
	}

	return 0.0;
}

int BarGraph::getBoxWidth()
{
	if (value.size() > 0)
	{
		return pos.w / value.size();
	}

	return 1;
}
