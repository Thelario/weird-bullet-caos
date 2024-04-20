#pragma once

#include <map>
#include <string>
#include <SDL_mixer.h>

namespace Satellite
{
	class SoundsManager
	{
		private:
			Mix_Music* _music;
			std::map<std::string, Mix_Chunk*> _sounds;

		public:
			static SoundsManager* Instance();

			bool Start();
			void Destroy();

			void PlayMusic();
			void PlaySound(const std::string& sound_id);
	};
}