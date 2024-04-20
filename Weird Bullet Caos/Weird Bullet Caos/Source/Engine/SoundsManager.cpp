#include "SoundsManager.h"

#include "LoggerManager.h"

namespace Satellite
{
	SoundsManager* SoundsManager::Instance()
	{
		static SoundsManager* instance = new SoundsManager();
		return instance;
	}

	bool SoundsManager::Start()
	{
		_music = Mix_LoadMUS("./assets/sounds/music.wav");
		if (_music == NULL) {
			LoggerManager::Error("Failed to load music! SDL_mixer Error: ", Mix_GetError());
			return false;
		}

		Mix_Chunk* ball_sound = Mix_LoadWAV("./assets/sounds/ball.wav");
		if (ball_sound == NULL) {
			LoggerManager::Error("Failed to ball sound! SDL_mixer Error: ", Mix_GetError());
			return false;
		}

		_sounds.emplace("ball-sound", ball_sound);

		return true;
	}

	void SoundsManager::Destroy()
	{
		for (auto sound : _sounds) {
			Mix_FreeChunk(sound.second);
		}

		_sounds.clear();

		Mix_FreeMusic(_music);
	}

	void SoundsManager::PlayMusic()
	{
		if (_music == NULL) {
			LoggerManager::Error("Trying to play the music when it is NULL.");
			return;
		}

		Mix_PlayMusic(_music, -1);
	}

	void SoundsManager::PlaySound(const std::string& sound_id)
	{
		if (_sounds.find(sound_id) == _sounds.end()) {
			LoggerManager::Error("Trying to play a sound that does not exist.");
			return;
		}

		Mix_PlayChannel(-1, _sounds.at(sound_id), 0);
	}
}