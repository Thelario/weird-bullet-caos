#pragma once

#include <vector>

#include "../Engine/GameObject.h"

#include "Bullet.h"

using namespace Satellite;

namespace BulletGame
{
	struct PlayerStats
	{
		float movement_speed;
		float rotation_speed;
		float bullet_speed;
		float fire_rate;
		int current_health;
		int max_health;
	};

	class Player : public GameObject
	{
	private:
		glm::vec2 direction;
		PlayerStats player_stats;
		float fire_rate_counter;

	public:
		Player(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
			bool flip_x, int tile_id = -1, bool center_aligned = true, int z_index = 0, SDL_Color color = { 255, 255, 255, 255 },
			bool enabled = true, bool renderable = true, bool collidable = false, glm::vec2 size = glm::vec2(0),
			glm::vec2 offset = glm::vec2(0), ColliderTag tag = ColliderTag::NONE);

		void Start() override;
		void Update() override;

		void OnCollisionEnter(GameObject* other) override;

		void MoveAndRotate();
		void Shoot();
	};
}