#include "Game.h"
#include "LoggerManager.h"
#include <iostream>

namespace Satellite
{
	void Game::Start() {
		LoggerManager::Error("Careful, you are not overriding the base Game class (Start).");
	}

	void Game::Update()
	{
		for (GameObject* game_object : gameobjects) {
			if (game_object != nullptr && game_object->enabled == true) {
				game_object->Update();
			}
		}
	}

	void Game::Render()
	{
		for (GameObject* game_object : gameobjects) {
			if (game_object != nullptr && game_object->enabled == true) {
				game_object->Render();
			}
		}
	}

	void Game::Destroy() {
		LoggerManager::Error("Careful, you are not overriding the base Game class (Destroy).");
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
		// It might be a better idea to mark all the pending to destroy objects as disable
		// and destroy one every frame, instead of all the objects each frame.

		for (GameObject* element_to_remove : gameobjects_to_remove)
		{
			auto it = std::find(gameobjects.begin(), gameobjects.end(), element_to_remove);
			gameobjects.erase(it);
			delete element_to_remove;
		}

		gameobjects_to_remove.clear();
	}
}