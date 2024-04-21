#pragma once

#include <glm/glm.hpp>

#include "Game.h"
#include "Random.h"

namespace Satellite
{
	class Engine
	{
		private:
			bool is_running;
			
			Uint32 milliseconds_previous_frame;
			double delta_time;

			glm::vec2 render_logical_size;

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

			void SetRenderLogicalSize(glm::vec2 logical_size);
	};
}