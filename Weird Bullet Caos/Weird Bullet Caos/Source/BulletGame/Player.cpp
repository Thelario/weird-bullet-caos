#include "Player.h"

#include <math.h>

#include "../Engine/SoundsManager.h"
#include "../Engine/LoggerManager.h"
#include "../Engine/InputManager.h"
#include "../Engine/Engine.h"

namespace BulletGame
{
	Player::Player(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable, bool collidable,
		glm::vec2 size, glm::vec2 offset, ColliderTag tag) : GameObject(position, scale, rotation, texture_id, width, height, flip_x, tile_id,
			center_aligned, z_index, color, enabled, renderable, collidable, size, offset, tag)
	{ }

	void Player::Start()
	{
		GameObject::Start();

		player_stats.movement_speed = 200;
		player_stats.rotation_speed = 100;
		player_stats.fire_rate = 0.5 * 1000;
		player_stats.bullet_speed = 700;

		direction = glm::vec2(0, 1);
		fire_rate_counter = SDL_GetTicks();
	}

	void Player::Update()
	{
		MoveAndRotate();
		Shoot();
	}

	void Player::MoveAndRotate()
	{
		double dt = Engine::Instance()->GetDeltaTime();

		// Gather rotation input

		if (InputManager::GetKeyDown(KeyCode::A)) {
			rotation -= player_stats.rotation_speed * dt;
		}

		if (InputManager::GetKeyDown(KeyCode::D)) {
			rotation += player_stats.rotation_speed * dt;
		}

		// Clamp the rotation

		if (rotation > 360) {
			rotation -= 360;
		}
		else if (rotation < 0) {
			rotation += 360;
		}

		// Degrees to radians

		double rotation_radians = (rotation - 90) * (M_PI / 180);
		direction = glm::vec2(cos(rotation_radians), sin(rotation_radians));

		// Move

		position.x += dt * player_stats.movement_speed * direction.x;
		position.y += dt * player_stats.movement_speed * direction.y;

		// Check if player outside the limits

		if (position.x < 0 || position.x > Engine::Instance()->GetWindowWidth() ||
			position.y < 0 || position.y > Engine::Instance()->GetWindowHeight()) {
			position = glm::vec2(Engine::Instance()->GetWindowWidth() / 2, Engine::Instance()->GetWindowHeight() / 2);
		}
	}

	void Player::Shoot()
	{
		if (InputManager::GetMouseButtonDown(0))
		{
			if (SDL_GetTicks() - fire_rate_counter >= player_stats.fire_rate)
			{
				fire_rate_counter = SDL_GetTicks();

				Bullet* bullet = new Bullet(position, glm::vec2(0.8, 1.6), rotation, "basic-shapes", 32, 32, false, 1, true,
					0, { 223, 208, 184, 255 }, true, true, true, glm::vec2(40, 40), glm::vec2(0), ColliderTag::BULLET, player_stats.bullet_speed, direction);

				Engine::Instance()->CreateObject(bullet);

				SoundsManager::Instance()->PlaySound("shoot");
			}
		}
	}

	void Player::OnCollisionEnter(GameObject* other)
	{
		if (other->CompareTag(ColliderTag::OBSTACLE))
		{
			SoundsManager::Instance()->PlaySound("player-hit");
			Engine::Instance()->DestroyObject(other);
		}
	}
}