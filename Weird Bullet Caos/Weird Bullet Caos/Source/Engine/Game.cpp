#include "Game.h"

#include <iostream>

#include "LoggerManager.h"
#include "Engine.h"

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

	void Game::HandleCollisions()
	{
		// AABB Collision: expensive but easy to implement O(n^2).

		for (auto i = gameobjects.begin(); i != gameobjects.end(); i++)
		{
			auto a = *i;

			if (a->collidable == false) {
				continue;
			}

			float pos_x = a->GetPosition().x - (a->GetSize().x / 2);
			float pos_y = a->GetPosition().y - (a->GetSize().y / 2);

			SDL_Rect a_rect = {
				static_cast<int>(pos_x + a->GetOffset().x),
				static_cast<int>(pos_y + a->GetOffset().y),
				static_cast<int>(a->GetSize().x),
				static_cast<int>(a->GetSize().y)
			};

			for (auto j = (i + 1); j != gameobjects.end(); j++)
			{
				auto b = *j;

				if (b->collidable == false) {
					continue;
				}

				float pos_x = b->GetPosition().x - (b->GetSize().x / 2);
				float pos_y = b->GetPosition().y - (b->GetSize().y / 2);

				SDL_Rect b_rect = {
					static_cast<int>(pos_x + b->GetOffset().x),
					static_cast<int>(pos_y + b->GetOffset().y),
					static_cast<int>(b->GetSize().x),
					static_cast<int>(b->GetSize().y)
				};

				if (SDL_HasIntersection(&a_rect, &b_rect)) // Collision!!!
				{
					a->HandleCollisionEvent(b);
					b->HandleCollisionEvent(a);

					if (Engine::Instance()->Debugging() == false) {
						continue;
					}

					a->SetColliderColor({ 255, 0, 0, 255 });
					b->SetColliderColor({ 255, 0, 0, 255 });
				}
				else
				{
					a->RestartCollisionData(b);
					b->RestartCollisionData(a);

					if (Engine::Instance()->Debugging() == false) {
						continue;
					}

					a->SetColliderColor({ 0, 255, 0, 255 });
					b->SetColliderColor({ 0, 255, 0, 255 });
				}
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