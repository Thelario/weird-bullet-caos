#include "Player.h"

#include <math.h>

#include "../Engine/InputManager.h"
#include "../Engine/Engine.h"

namespace BulletGame
{
	Player::Player(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color)
		: GameObject(position, scale, rotation, texture_id, width, height, flip_x, tile_id, center_aligned, z_index, color),
		error(2), current_limit(0), direction(glm::vec2(0)), speed(0), fire_rate(0), fire_rate_counter(0), bullet_speed(0)
	{
		limits[0] = glm::vec2(Engine::Instance()->GetWindowWidth() / 3, 24);
		limits[1] = glm::vec2(Engine::Instance()->GetWindowWidth() / 3, Engine::Instance()->GetWindowHeight() - 24);
		limits[2] = glm::vec2(Engine::Instance()->GetWindowWidth() - 32, Engine::Instance()->GetWindowHeight() - 24);
		limits[3] = glm::vec2(Engine::Instance()->GetWindowWidth() - 32, 24);
	}

	Player::~Player()
	{
		for (Bullet* bullet : bullets) {
			delete bullet;
		}

		bullets.clear();
	}

	void Player::Start()
	{
		GameObject::Start();

		position = limits[current_limit];
		direction = glm::normalize(limits[(current_limit + 1) % 4] - position);
		speed = 100; // max 200
		fire_rate = 0.5 * 1000;
		fire_rate_counter = SDL_GetTicks();
		bullet_speed = 150;
	}

	void Player::Update()
	{
		// Moving the player

		position.x += Engine::Instance()->GetDeltaTime() * speed * direction.x;
		position.y += Engine::Instance()->GetDeltaTime() * speed * direction.y;

		if (glm::distance(limits[(current_limit + 1) % 4], position) <= error) {
			current_limit = (current_limit + 1) % 4;
			position = limits[current_limit];
			direction = glm::normalize(limits[(current_limit + 1) % 4] - position);
		}

		// Rotating the player to point towards mouse position
		
		glm::vec2 mouse_pos = InputManager::GetMousePosition();
		glm::vec2 delta_pos = mouse_pos - position;
		rotation = ((atan2(delta_pos.y, delta_pos.x) * 180.0) / M_PI) + 90;

		// Shoot a bullet

		if (InputManager::GetMouseButtonDown(0))
		{
			if (SDL_GetTicks() - fire_rate_counter >= fire_rate)
			{
				fire_rate_counter = SDL_GetTicks();

				glm::vec2 direction = glm::normalize(delta_pos);
				glm::vec2 new_pos = glm::vec2(position.x + 1.2 * direction.x, position.y + 1.2 * direction.y);

				Bullet* bullet = new Bullet(position, glm::vec2(1), rotation, "bullet", 16, 16, false, -1, true,
					0, { 255, 255, 255, 255 }, bullet_speed, direction);
				
				Engine::Instance()->CreateObject(bullet);
			}
		}
	}
}