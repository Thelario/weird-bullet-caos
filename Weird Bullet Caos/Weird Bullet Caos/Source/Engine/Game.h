#pragma once

#include <vector>

#include "GameObject.h"

namespace Satellite
{
	class Game
	{
	private:
		std::vector<GameObject*> gameobjects;
		std::vector<GameObject*> gameobjects_to_add;
		std::vector<GameObject*> gameobjects_to_remove;

	public:
		virtual void Start();
		virtual void Update();
		void Render();
		void Destroy();

		void CreateObject(GameObject* game_object);
		void DestroyObject(GameObject* game_object);

		void CreateGameObjects();
		void DestroyGameObjects();
	};
}