#include "pch.h"

#include "Engine.h"

#include <iostream>

namespace Satellite
{
	void Engine::Start(Game* game)
	{
		_game = game;

		_game->Start();
	}

	void Engine::Run()
	{
		_game->Update();
	}

	void Engine::Destroy()
	{
		_game->Destroy();
	}
}