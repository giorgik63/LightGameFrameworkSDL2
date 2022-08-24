#include "AudioPlayer.h"
#include "item.h"

#include <SDL_messagebox.h>
#include <iostream>
#include <fstream>>

AudioPlayer::AudioPlayer()
{
	SDL_AudioSpec pref;
	SDL_memset(&pref, 0, sizeof(pref));
	SDL_memset(&specs, 0, sizeof(specs));
	pref.freq = 16000;
	pref.format = AUDIO_U8;
	pref.channels = 1;
	pref.samples = 1024;
	pref.callback = NULL;

	dev = SDL_OpenAudioDevice(NULL, 0, &pref, &specs, 0);
	if (dev < 1)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "AudioPlayer", "Could not open an audio playback device, please check that speakers are available to the system", NULL);
	}
}

SDL_AudioSpec AudioPlayer::getSpec()
{
	return this->specs;
}

void AudioPlayer::setSpec(SDL_AudioSpec newSpec)
{
	SDL_PauseAudioDevice(dev, 1);
	SDL_CloseAudioDevice(dev);

	dev = SDL_OpenAudioDevice(NULL, SDL_FALSE, &newSpec, &specs, 0);
}

int AudioPlayer::fileSize(std::string path)
{
	std::ifstream file(path.c_str());
	file.seekg(file.end);

	int val = file.tellg();

	file.close();

	return val;
}

void AudioPlayer::loadWav(std::string path)
{
	SDL_AudioSpec newspec;
	SDL_memset(&newspec, 0, sizeof(newspec));

	Uint32 length = fileSize(path);

	data.reserve(length + 1);

	Uint8* buffer;

	SDL_LoadWAV(path.c_str(), &specs, &buffer, &length);

	dev = SDL_OpenAudioDevice(NULL, SDL_FALSE, &newspec, &specs, 0);

	for (int i = 0; i < length; i++)
	{
		data.push_back(buffer[i]);
	}

	SDL_QueueAudio(dev, &data[0], data.size());
	SDL_FreeWAV(buffer);

	std::cout << "Freq: " << specs.freq << " Formt: " << specs.format << " chans: " << specs.channels << " samples: " << specs.samples << std::endl;
}

void AudioPlayer::loadRaw(std::string path)
{
	int length = fileSize(path);

	data.reserve(length + 1);

	std::ifstream ifile(path.c_str(), std::ios::binary);
	ifile.read((char*)(&data[0]), length);
	ifile.close();

	SDL_QueueAudio(dev, &data[0], length);
}

void AudioPlayer::loadRaw(std::vector <Uint8> data)
{
	this->data = data;

	SDL_ClearQueuedAudio(dev);
	SDL_QueueAudio(dev, &data[0], data.size());
}

void AudioPlayer::play()
{
	SDL_PauseAudioDevice(dev, 0);
}

void AudioPlayer::pause()
{
	SDL_PauseAudioDevice(dev, 1);

}

void AudioPlayer::stop()
{
	SDL_PauseAudioDevice(dev, 1);
	SDL_ClearQueuedAudio(dev);
	SDL_QueueAudio(dev, &data[0], data.size());
}

void AudioPlayer::clear()
{
	pause();

	data.clear();

	SDL_ClearQueuedAudio(dev);
}
