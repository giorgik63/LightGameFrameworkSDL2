#pragma once

#include <SDL_audio.h>

#include <vector>

#include "AudioPlayer.h"

class Recorder
{
public:
	// defaults to a data-saver spec
	Recorder();
	~Recorder();

	SDL_AudioSpec getSpec();
	void setSpec(SDL_AudioSpec newSpec);

	AudioPlayer* getPlayer();

	void record();
	void pause();
	void resume();
	void play();
	void clear();

	std::vector <Uint8> getData();

	void save(std::string filePath);

private:
	SDL_AudioSpec specs;
	SDL_AudioDeviceID dev;

	std::vector <Uint8> data;

	// SDL states that a player device should be opened
	// before a recording device, so now we have an internal
	// audioplayer for playback.
	AudioPlayer* player;


};
