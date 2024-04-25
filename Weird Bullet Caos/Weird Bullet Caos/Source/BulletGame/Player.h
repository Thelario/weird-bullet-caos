#pragma once

#include <vector>

#include "../Engine/GameObject.h"

#include "Bullet.h"

using namespace Satellite;

namespace BulletGame
{
	class Player : public GameObject
	{
	private:
		glm::vec2 direction;
		float movement_speed;
		float rotation_speed;
		float bullet_speed;
		float fire_rate;
		float fire_rate_counter;

		std::vector<Bullet*> bullets;

	public:
		Player(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
			bool flip_x, int tile_id = -1, bool center_aligned = true, int z_index = 0, SDL_Color color = { 255, 255, 255, 255 });

		void Start() override;
		void Update() override;

		void MoveAndRotate();
		void Shoot();
	};
}