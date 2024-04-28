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
		void HandleCollisions();
		void Render();
		void Destroy();

		void CreateObject(GameObject* gameobject);
		void DestroyObject(GameObject* gameobject);
		void DestroyObjects();

		void CreateGameObjects();
		void DestroyGameObjects();
	};
}