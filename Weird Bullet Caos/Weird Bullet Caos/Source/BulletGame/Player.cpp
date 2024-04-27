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
		glm::vec2 size, glm::vec2 offset) : GameObject(position, scale, rotation, texture_id, width, height, flip_x, tile_id,
			center_aligned, z_index, color, enabled, renderable, collidable, size, offset)
	{ }

	void Player::Start()
	{
		GameObject::Start();

		direction = glm::vec2(0, 1);
		movement_speed = 200;
		rotation_speed = 100;
		fire_rate = 0.5 * 1000;
		fire_rate_counter = SDL_GetTicks();
		bullet_speed = 700;
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

		if (InputManager::GetKey(KeyCode::A)) {
			rotation -= rotation_speed * dt;
		}

		if (InputManager::GetKey(KeyCode::D)) {
			rotation += rotation_speed * dt;
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

		position.x += dt * movement_speed * direction.x;
		position.y += dt * movement_speed * direction.y;

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
			if (SDL_GetTicks() - fire_rate_counter >= fire_rate)
			{
				fire_rate_counter = SDL_GetTicks();

				Bullet* bullet = new Bullet(position, glm::vec2(0.8, 1.6), rotation, "basic-shapes", 32, 32, false, 1, true,
					0, { 255, 255, 255, 255 }, true, true, true, glm::vec2(40, 40), glm::vec2(0), bullet_speed, direction);

				Engine::Instance()->CreateObject(bullet);

				SoundsManager::Instance()->PlaySound("shoot");
			}
		}
	}

	void Player::OnCollisionEnter(GameObject* other)
	{
		LoggerManager::Log("Player collision enter.");
	}

	void Player::OnCollisionStay(GameObject* other)
	{
		LoggerManager::Log("Player collision stay.");
	}

	void Player::OnCollisionExit(GameObject* other)
	{
		LoggerManager::Log("Player collision exit.");
	}
}