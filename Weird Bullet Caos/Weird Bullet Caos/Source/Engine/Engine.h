#pragma once

#include "Game.h"
#include "Random.h"

namespace Satellite
{
	class Engine
	{
		private:
			Uint32 milliseconds_previous_frame;
			double delta_time;
			bool is_running;

			SDL_Window* window;
			SDL_Renderer* renderer;
			Random* random;
			Game* game;

		public:
			static Engine* Instance();

			void Start(Game* game_to_run);
			void Run();
			void Destroy();

			void ProcessInput();
			void Update();
			void Render();
	};
}