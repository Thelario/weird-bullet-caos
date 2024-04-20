#include "pch.h"

#include "Engine.h"

namespace Satellite
{
	Engine* Engine::instance()
	{
		static Engine* instance = new Engine();
		return instance;
	}

	void Engine::Start(Game* game)
	{
		// Start up engine systems in the correct order.

		_logger = new LoggerManager();

		_game = game;

		_game->Start();
	}

	void Engine::Run()
	{
		_game->Update();
	}

	void Engine::Destroy()
	{
		// Shut everything down, in reverse order.

		_game->Destroy();

		delete _logger;
	}
}