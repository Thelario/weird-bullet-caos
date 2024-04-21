#include "Engine.h"

#include <iostream>
#include <ctime>
#include <chrono>

#include "InputManager.h"
#include "LoggerManager.h"
#include "FontsManager.h"
#include "SoundsManager.h"
#include "TexturesManager.h"

const char* title = "Weird Bullet Caos";
const int width = 960;
const int height = 540;

namespace Satellite
{
	Engine* Engine::Instance()
	{
		static Engine* instance = new Engine();
		return instance;
	}

	void Engine::Start(Game* game_to_run)
	{
		// Start up engine systems in the correct order.

		// Initializing SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			LoggerManager::Error("An error was produced when initializing SDL: ", SDL_GetError());
			is_running = false;
			return;
		}

		// Initializing TTF
		if (TTF_Init() != 0) {
			LoggerManager::Error("An error was produced when initializing TTF: ", TTF_GetError());
			is_running = false;
			return;
		}

		// Creating SDL Window
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			LoggerManager::Error("An error was produced when creating SDL window: ", SDL_GetError());
			is_running = false;
			return;
		}

		// Creating SDL Renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) {
			LoggerManager::Error("An error was produced when creating SDL renderer: ", SDL_GetError());
			is_running = false;
			return;
		}

        // Initializing SDL_Mixer
		Mix_Init(MIX_INIT_WAVPACK);

        // Initializing all managers
		FontsManager::Instance()->Start();
		SoundsManager::Instance()->Start();
		TexturesManager::Instance()->Start(renderer);

		// Creating random based on system time
		auto now = std::chrono::system_clock::now();
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);
		std::tm local_tm;
		localtime_s(&local_tm, &now_time);
		int seed = (local_tm.tm_hour * 60 * 60) + (local_tm.tm_min * 60) + local_tm.tm_sec;
		random = new Random(seed);

        // Start the selected game
		game = game_to_run;
		game->Start();

        // After the game has had a chance to change some of the Engine values, apply those engine values

        if (SDL_RenderSetLogicalSize(renderer, render_logical_size.x, render_logical_size.y) != 0) {
            LoggerManager::Error("An error was produced when setting up the render logical size: ", SDL_GetError());
            is_running = false;
            return;
        }

		is_running = true;
	}

	void Engine::Run()
	{
		while (is_running)
		{
			delta_time = (SDL_GetTicks() - milliseconds_previous_frame) / 1000.0;
			if (delta_time > 1000) {
				delta_time = 0;
			}

			milliseconds_previous_frame = SDL_GetTicks();

			ProcessInput();
			game->Update();
			game->Render(renderer);
		}
	}

    void Engine::ProcessInput()
    {
        SDL_Event event;

        InputManager::SetMouseButtonUp(0, false);
        InputManager::SetMouseButtonUp(1, false);

        while (SDL_PollEvent(&event)) // Iterating through all the possible events that might have happened in this frame
        {
            Uint32 buttonState = SDL_GetMouseState(NULL, NULL);
            switch (event.type)
            {
            case SDL_QUIT:
                is_running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_o:
                    InputManager::SetKey(KeyCode::O, true);
                    break;
                case SDLK_w:
                    InputManager::SetKey(KeyCode::W, true);
                    break;
                case SDLK_s:
                    InputManager::SetKey(KeyCode::S, true);
                    break;
                case SDLK_l:
                    InputManager::SetKey(KeyCode::L, true);
                    break;
                case SDLK_ESCAPE:
                    InputManager::SetKey(KeyCode::ESCAPE, true);
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_o:
                    InputManager::SetKey(KeyCode::O, false);
                    break;
                case SDLK_w:
                    InputManager::SetKey(KeyCode::W, false);
                    break;
                case SDLK_s:
                    InputManager::SetKey(KeyCode::S, false);
                    break;
                case SDLK_l:
                    InputManager::SetKey(KeyCode::L, false);
                    break;
                case SDLK_ESCAPE:
                    InputManager::SetKey(KeyCode::ESCAPE, false);
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                InputManager::SetMousePosition(glm::vec2(event.motion.x, event.motion.y));
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    InputManager::SetMouseButtonDown(0, true);
                    break;
                case SDL_BUTTON_RIGHT:
                    InputManager::SetMouseButtonDown(1, true);
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    InputManager::SetMouseButtonDown(0, false);
                    InputManager::SetMouseButtonUp(0, true);
                    break;
                case SDL_BUTTON_RIGHT:
                    InputManager::SetMouseButtonDown(1, false);
                    InputManager::SetMouseButtonUp(1, true);
                    break;
                }
                break;
            }
        }
    }

    void Engine::Update()
    {
        game->Update();
    }

    void Engine::Render()
    {
        SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
        SDL_RenderClear(renderer);

        game->Render(renderer);

        SDL_RenderPresent(renderer);
    }

	void Engine::Destroy()
	{
		// Shut everything down, in reverse order.

		game->Destroy();
        
        delete random;

        TexturesManager::Instance()->Destroy();
        SoundsManager::Instance()->Destroy();
        FontsManager::Instance()->Destroy();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        Mix_Quit();
        TTF_Quit();
        SDL_Quit();
	}

    void Engine::SetRenderLogicalSize(glm::vec2 logical_size) { render_logical_size = logical_size; }
}