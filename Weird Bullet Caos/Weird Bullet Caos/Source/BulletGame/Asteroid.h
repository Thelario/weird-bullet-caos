#pragma once

#include "../Engine/GameObject.h"

using namespace Satellite;

namespace BulletGame
{
	class Asteroid : public GameObject
	{
	private:
		float speed;
		glm::vec2 direction;
		
		GameObject* player;

	public:
		Asteroid(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
			bool flip_x, int tile_id = -1, bool center_aligned = true, int z_index = 0, SDL_Color color = { 255, 255, 255, 255 },
			bool enabled = true, bool renderable = true, bool collidable = false, glm::vec2 size = glm::vec2(0),
			glm::vec2 offset = glm::vec2(0), ColliderTag tag = ColliderTag::OBSTACLE, float speed = 0, glm::vec2 direction = glm::vec2(0),
			GameObject* player = nullptr);

		void Update() override;

		void OnCollisionEnter(GameObject* other) override;
	};
}