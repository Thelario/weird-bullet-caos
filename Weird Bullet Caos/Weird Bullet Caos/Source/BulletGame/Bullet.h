#pragma once

#include "../Engine/GameObject.h"

using namespace Satellite;

namespace BulletGame
{
	class Bullet : public GameObject
	{
	private:
		float speed;
		glm::vec2 direction;

	public:
		Bullet(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
			bool flip_x, int tile_id = -1, bool center_aligned = true, int z_index = 0, SDL_Color color = { 255, 255, 255, 255 },
			float speed = 0, glm::vec2 direction = glm::vec2(0));

		void Start() override;
		void Update() override;
	};
}