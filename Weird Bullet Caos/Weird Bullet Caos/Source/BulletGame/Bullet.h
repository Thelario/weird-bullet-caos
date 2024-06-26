#pragma once

#include "../Engine/GameObject.h"

using namespace Satellite;

namespace BulletGame
{
	class BulletGame;
	class Bullet : public GameObject
	{
	private:
		BulletGame* bullet_game;
		
		float speed;
		glm::vec2 direction;

	public:
		Bullet(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
			bool flip_x, int tile_id = -1, bool center_aligned = true, int z_index = 0, SDL_Color color = { 255, 255, 255, 255 },
			bool enabled = true, bool renderable = true, bool collidable = false, glm::vec2 size = glm::vec2(0),
			glm::vec2 offset = glm::vec2(0), ColliderTag tag = ColliderTag::BULLET, float speed = 0, glm::vec2 direction = glm::vec2(0),
			BulletGame* bullet_game = nullptr);

		void Update() override;

		void OnCollisionEnter(GameObject* other) override;
	};
}