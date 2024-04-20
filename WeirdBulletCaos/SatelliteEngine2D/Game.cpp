#include "pch.h"

#include "Game.h"
#include "Engine.h"

namespace Satellite
{
	void Game::Start()
	{
		Engine::instance()->GetLogger()->Error("Careful, you are not override the base Game class.");
	}

	void Game::Update()
	{
		Engine::instance()->GetLogger()->Error("Careful, you are not override the base Game class.");
	}

	void Game::Destroy()
	{
		Engine::instance()->GetLogger()->Error("Careful, you are not override the base Game class.");
	}
}