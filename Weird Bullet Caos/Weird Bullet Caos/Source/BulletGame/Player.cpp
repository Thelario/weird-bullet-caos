#include "Player.h"

#include "../Engine/Engine.h"

namespace BulletGame
{
	Player::Player(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color)
		: GameObject(position, scale, rotation, texture_id, width, height, flip_x, tile_id, center_aligned, z_index, color)
	{
		limits[0] = glm::vec2(Engine::Instance()->GetWindowWidth() / 3 + 3, 34);
		limits[1] = glm::vec2(Engine::Instance()->GetWindowWidth() / 3 + 3, Engine::Instance()->GetWindowHeight() - 32);
		limits[2] = glm::vec2(Engine::Instance()->GetWindowWidth() - 34, Engine::Instance()->GetWindowHeight() - 32);
		limits[3] = glm::vec2(Engine::Instance()->GetWindowWidth() - 34, 34);

		error = 1;
		current_limit = 0;
	}

	void Player::Start()
	{
		GameObject::Start();
		position = limits[current_limit];
		direction = glm::normalize(limits[(current_limit + 1) % 4] - position);
		speed = 100; // max 200
	}

	void Player::Update()
	{
		position.x += Engine::Instance()->GetDeltaTime() * speed * direction.x;
		position.y += Engine::Instance()->GetDeltaTime() * speed * direction.y;

		if (glm::distance(limits[(current_limit + 1) % 4], position) <= error) {
			current_limit = (current_limit + 1) % 4;
			position = limits[current_limit];
			direction = glm::normalize(limits[(current_limit + 1) % 4] - position);
		}
	}
}