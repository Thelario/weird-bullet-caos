#include "pch.h"

#include "Game.h"
#include "LoggerManager.h"

namespace Satellite
{
	void Game::Start()
	{
		LoggerManager::Error("Careful, you are not override the base Game class.");
	}

	void Game::Update()
	{
		LoggerManager::Error("Careful, you are not override the base Game class.");
	}

	void Game::Destroy()
	{
		LoggerManager::Error("Careful, you are not override the base Game class.");
	}
}