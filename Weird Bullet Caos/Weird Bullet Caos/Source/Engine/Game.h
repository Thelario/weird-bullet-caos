#pragma once

#include <SDL.h>

namespace Satellite
{
	class Game
	{
		public:
			virtual void Start();
			virtual void Update();
			virtual void Render(SDL_Renderer* renderer);
			virtual void Destroy();
	};
}