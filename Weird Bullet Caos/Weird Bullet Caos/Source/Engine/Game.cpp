#include "Game.h"
#include "LoggerManager.h"

namespace Satellite
{
	void Game::Start()
	{
		LoggerManager::Error("Careful, you are not overriding the base Game class (Start).");
	}

	void Game::Update()
	{
		LoggerManager::Error("Careful, you are not overriding the base Game class (Update).");
	}

	void Game::Render(SDL_Renderer* renderer)
	{
		LoggerManager::Error("Careful, you are not overriding the base Game class (Render).");
	}

	void Game::Destroy()
	{
		LoggerManager::Error("Careful, you are not overriding the base Game class (Destroy).");
	}
}