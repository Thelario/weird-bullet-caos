#include "Engine.h"

#include <iostream>
#include <ctime>
#include <chrono>

#include "InputManager.h"
#include "LoggerManager.h"
#include "FontsManager.h"
#include "SoundsManager.h"
#include "TexturesManager.h"

namespace Satellite
{
    const char* title = "Satellite";

	Engine* Engine::Instance()
	{
        static Engine* instance = new Engine();
		return instance;
	}

	void Engine::Start(Game* game_to_run)
	{
		// Start up engine systems in the correct order.

        // Initialize variables that can later be changed
        real_window_size = glm::vec2(1920, 1080);
        render_logical_size = glm::vec2(960, 540);

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
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, real_window_size.x, real_window_size.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

        // After the game has had a chance to change some of the Engine values, apply those engine values

        // Start the selected game
        game = game_to_run;
        game->Start();

        if (SDL_RenderSetLogicalSize(renderer, render_logical_size.x, render_logical_size.y) != 0) {
            LoggerManager::Error("An error was produced when setting up the render logical size: ", SDL_GetError());
            is_running = false;
            return;
        }

        //SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        //SDL_SetWindowSize(window, real_window_size.x, real_window_size.y);

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
            Update();
            Render();
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
        SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a);
        SDL_RenderClear(renderer);

        game->Render();

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

    int Engine::GetWindowWidth() { return render_logical_size.x; }
    int Engine::GetWindowHeight() { return render_logical_size.y; }
    double Engine::GetDeltaTime() { return delta_time; }
    SDL_Renderer* Engine::GetRenderer() { return renderer; }

    void Engine::SetBackgroundColor(SDL_Color color) { background_color = color; }
    void Engine::SetIsRunning(bool is_running) { this->is_running = is_running; }
    void Engine::SetWindowTitle(const char* new_title) { SDL_SetWindowTitle(window, new_title); }
    void Engine::SetRealWindowSize(glm::vec2 window_size) { real_window_size = window_size; }
    void Engine::SetRenderLogicalSize(glm::vec2 logical_size) { render_logical_size = logical_size; }
}