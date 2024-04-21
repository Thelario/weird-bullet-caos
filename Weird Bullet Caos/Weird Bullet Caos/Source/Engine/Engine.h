#pragma once

#include <glm/glm.hpp>
#include <SDL.h>

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

			SDL_Color background_color;
			glm::vec2 real_window_size;
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

			int GetWindowWidth();
			int GetWindowHeight();
			double GetDeltaTime();
			SDL_Renderer* GetRenderer();

			void SetBackgroundColor(SDL_Color color);
			void SetIsRunning(bool is_running);
			void SetWindowTitle(const char* new_title);
			void SetRealWindowSize(glm::vec2 window_size);
			void SetRenderLogicalSize(glm::vec2 logical_size);
	};
}