#pragma once

#include <SDL_audio.h>
#include <string>
#include <vector>

class AudioPlayer
{
public:
	AudioPlayer();

	SDL_AudioSpec getSpec();
	void setSpec(SDL_AudioSpec newSpec);

	void loadWav(std::string path);

	int fileSize(std::string path);

	// loads raw data, assumes you the user know what settings for the specs
	void loadRaw(std::string path);
	void loadRaw(std::vector <Uint8> data);

	void play();

	// stop the music, allow to restart from here
	void pause();

	// stop the music and reset to beginning
	void stop();

	// stop the music and clear the buffers
	void clear();

private:
	SDL_AudioSpec specs;
	SDL_AudioDeviceID dev;

	std::vector <Uint8> data;
};
