#pragma once

#include "item.h"

// may also be used for loot boxes and item interaction.
class Npc : public Item
{
public:
	Npc(SDL_Renderer* rend);

	//	void addTalk(prompt talk);
	void playTalk();
	void hurt(double atk);
	void heal(double val);
	void kill(); // play animation of npc... ending.

private:
	double maxHp, hp, atk, def;

	//	std::vector <prompt> talks;

	Item profile; // headshot image while prompt talking

	int activeTalk;
};
