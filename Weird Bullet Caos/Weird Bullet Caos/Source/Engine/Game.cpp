#include "Game.h"

#include <iostream>

#include "LoggerManager.h"

namespace Satellite
{
	void Game::Start() {
		LoggerManager::Error("Careful, you are not overriding the base Game class (Start).");
	}

	void Game::Update()
	{
		// We only update objects that are enabled

		for (GameObject* game_object : gameobjects)
		{
			if (game_object != nullptr && game_object->enabled == true) {
				game_object->Update();
			}
		}
	}

	void Game::Render()
	{
		// We only render objects that are enabled and are marked as renderable

		for (GameObject* game_object : gameobjects)
		{
			if (game_object != nullptr && game_object->enabled == true && game_object->renderable == true) {
				game_object->Render();
			}
		}
	}

	void Game::Destroy()
	{
		for (GameObject* game_object : gameobjects) {
			delete game_object;
		}
	}

	void Game::CreateObject(GameObject* game_object)
	{
		gameobjects_to_add.push_back(game_object);
	}

	void Game::DestroyObject(GameObject* game_object)
	{
		gameobjects_to_remove.push_back(game_object);
	}

	void Game::CreateGameObjects()
	{
		for (GameObject* game_object : gameobjects_to_add) {
			game_object->Start();
			gameobjects.push_back(game_object);
		}

		gameobjects_to_add.clear();
	}

	void Game::DestroyGameObjects()
	{
		for (GameObject* element_to_remove : gameobjects_to_remove)
		{
			auto it = std::find(gameobjects.begin(), gameobjects.end(), element_to_remove);
			gameobjects.erase(it);
			delete element_to_remove;
		}

		gameobjects_to_remove.clear();
	}
}