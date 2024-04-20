#include "pch.h"

#include "Game.h"

#include <iostream>

namespace Satellite
{
	void Game::Start()
	{
		std::cout << "Careful, you are not override the base Game class." << std::endl;
	}

	void Game::Update()
	{
		std::cout << "Careful, you are not override the base Game class." << std::endl;
	}

	void Game::Destroy()
	{
		std::cout << "Careful, you are not override the base Game class." << std::endl;
	}
}