#pragma once

#include "../Engine/GameObject.h"

using namespace Satellite;

namespace BulletGame
{
	class Obstacle : public GameObject
	{
	private:
		float speed;
		glm::vec2 direction;

	public:
		Obstacle(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
			bool flip_x, int tile_id = -1, bool center_aligned = true, int z_index = 0, SDL_Color color = { 255, 255, 255, 255 },
			bool enabled = true, bool renderable = true, float speed = 0, glm::vec2 direction = glm::vec2(0));

		void Update() override;
	};
}