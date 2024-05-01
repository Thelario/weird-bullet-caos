#include "Spawner.h"

#include "../Engine/LoggerManager.h"
#include "../Engine/Engine.h"

#include "Asteroid.h"
#include "HealthPowerup.h"
#include "BulletGame.h"

namespace BulletGame
{
	const float obstacles_speed_multiplier = 0.2;
	const float time_between_obstacles_multiplier = 0.2;

	Spawner::Spawner(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable,
		GameObject* player)
		: GameObject(position, scale, rotation, texture_id, width, height, flip_x, tile_id, center_aligned, z_index,
			color, enabled, renderable), player(player)
	{ }

	void Spawner::Start()
	{
		GameObject::Start();

		obstacles[0] = { "asteroid-small", glm::vec2(60, 60) };
		obstacles[1] = { "asteroid-large", glm::vec2(100, 100) };
		obstacles[2] = { "asteroid-square-small", glm::vec2(60, 60) };
		obstacles[3] = { "asteroid-square-large", glm::vec2(100, 100) };

		obstacles_speed = 200;
		spawn_distance_from_center = 1200;
		previous_time_between_obstacles = SDL_GetTicks();
		time_between_obstacles = 2500;
	}

	void Spawner::Update()
	{
		// Spawn obstacles

		if (SDL_GetTicks() >= previous_time_between_obstacles + time_between_obstacles)
		{
			previous_time_between_obstacles = SDL_GetTicks();

			// Create an obstacle on a random point in a circunference from center

			glm::vec2 position = glm::vec2(Engine::Instance()->GetWindowWidth() / 2, Engine::Instance()->GetWindowHeight() / 2);
			glm::vec2 direction = glm::vec2(0);
				
			do {
				direction.x = Engine::Instance()->GetRandom()->GenerateRandomFloat(-1, 1);
				direction.y = Engine::Instance()->GetRandom()->GenerateRandomFloat(-1, 1);
			}
			while (direction == glm::vec2(0));
			
			direction = glm::normalize(direction);

			position.x += direction.x * spawn_distance_from_center;
			position.y += direction.y * spawn_distance_from_center;

			direction = player->GetPosition() - position;
			direction = glm::normalize(direction);

			ObstacleInfo obstacle = obstacles[Engine::Instance()->GetRandom()->GenerateRandomInteger(0, 3)];

			Engine::Instance()->CreateObject(new Asteroid(glm::vec2(position.x, position.y),
				glm::vec2(1), 0, obstacle.id, 128, 128, false, -1, true, 0, { 148, 137, 121, 255 },
				true, true, true, obstacle.collider_size, glm::vec2(0), ColliderTag::OBSTACLE, obstacles_speed, direction, player));
		}
	}

	void Spawner::IncreaseDifficulty()
	{
		obstacles_speed += obstacles_speed * obstacles_speed_multiplier;
		time_between_obstacles -= time_between_obstacles * time_between_obstacles_multiplier;
	}

	void Spawner::SpawnHealthPowerup()
	{
		// Create a health powerup on a random point in a circunference from center

		glm::vec2 position = glm::vec2(Engine::Instance()->GetWindowWidth() / 2, Engine::Instance()->GetWindowHeight() / 2);
		glm::vec2 direction = glm::vec2(0);

		do {
			direction.x = Engine::Instance()->GetRandom()->GenerateRandomFloat(-1, 1);
			direction.y = Engine::Instance()->GetRandom()->GenerateRandomFloat(-1, 1);
		} while (direction == glm::vec2(0));

		direction = glm::normalize(direction);

		position.x += direction.x * spawn_distance_from_center;
		position.y += direction.y * spawn_distance_from_center;

		direction = player->GetPosition() - position;
		direction = glm::normalize(direction);

		Engine::Instance()->CreateObject(new HealthPowerup(glm::vec2(position.x, position.y),
			glm::vec2(1), 0, "health-powerup", 128, 128, false, -1, true, 0, { 250, 112, 112, 255 },
			true, true, true, glm::vec2(70), glm::vec2(0), ColliderTag::HEALTH_POWERUP, 200, direction, player));
	}
}