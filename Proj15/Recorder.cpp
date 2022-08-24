#include "Recorder.h"

#include <SDL_messagebox.h>

#include <fstream>

Recorder::Recorder()
{
	player = new AudioPlayer;

	SDL_AudioSpec pref;

	SDL_memset(&pref, 0, sizeof(pref));
	SDL_memset(&specs, 0, sizeof(specs));
	pref.freq = 16000;
	pref.format = AUDIO_U8;
	pref.channels = 1;
	pref.samples = 1024;
	pref.callback = NULL;

	dev = SDL_OpenAudioDevice(NULL, 1, &pref, &specs, 0);
	if (dev < 1)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Recorder", "Please enable your microphone for recording", NULL);
	}
}

Recorder::~Recorder()
{
	delete player;
}

SDL_AudioSpec Recorder::getSpec()
{
	return specs;
}

void Recorder::setSpec(SDL_AudioSpec newSpec)
{
	SDL_CloseAudioDevice(dev);

	player->setSpec(newSpec);

	SDL_AudioSpec tempSpec = player->getSpec();

	dev = SDL_OpenAudioDevice(NULL, SDL_FALSE, &newSpec, &specs, 0);
}

AudioPlayer* Recorder::getPlayer()
{
	return player;
}

void Recorder::record()
{
	SDL_PauseAudioDevice(dev, 0);
}

void Recorder::pause()
{
	player->pause();

	SDL_PauseAudioDevice(dev, 1);
}

void Recorder::resume()
{
	SDL_PauseAudioDevice(dev, 0);
}

void Recorder::play()
{
	int samples = specs.samples;

	Uint8* buffer = new Uint8[samples];

	int ret = samples;
	while (ret == samples)
	{
		ret = SDL_DequeueAudio(dev, buffer, samples);

		for (int i = 0; i < ret; i++)
		{
			data.push_back(buffer[i]);
		}
	}

	delete[] buffer;

	player->loadRaw(this->data);
	player->play();
}

void Recorder::clear()
{
	player->clear();
	data.clear();

	SDL_ClearQueuedAudio(dev);
}

std::vector <Uint8> Recorder::getData()
{
	return data;
}

void Recorder::save(std::string filePath)
{
	std::ofstream ofile(filePath.c_str(), std::ios::binary);

	ofile.write((char*)(&data[0]), data.size());
	ofile.close();
}
