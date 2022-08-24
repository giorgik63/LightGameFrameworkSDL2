#pragma once

#include "item.h"

// Create a bar graph out of given data points.
// Each value input should also be given a string name, name may be a date,
// 	a place, a description. 
// todo: sort by name, sort by value

class BarGraph : public Item
{
public:
	BarGraph(SDL_Renderer* rend, int x, int y, int w, int h);

	// alpha is ignored unless user calls SDL_SetRenderDrawBlendMode(...);
	void setBarColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setBkgImage(std::string imagePath);
	void addValue(std::string name, double val);

	//	box * getBox(int x, int y); // get the box for witch the points collide.
	std::string getLabel(int index);

	double getValue(int index);

	int getBoxWidth();

	void refresh();

private:
	Item bkg;

	double maxVal, minVal;

	int sampleCount;

	// Consider using a map instead of two vectors...
	std::vector <std::string> name;
	std::vector <double> value;

	Uint8 rbar, gbar, bbar, abar;
};
