#include "Asteroid.h"

#include "../Engine/Engine.h"

namespace BulletGame
{
	const float distance_from_player = 2200;

	Asteroid::Asteroid(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable, float speed,
		glm::vec2 direction, GameObject* player) : GameObject(position, scale, rotation, texture_id, width, height, flip_x,
			tile_id, center_aligned, z_index, color), speed(speed), direction(direction), player(player)
	{ }

	void Asteroid::Update()
	{
		// Move obstacle

		position.x += Engine::Instance()->GetDeltaTime() * speed * direction.x;
		position.y += Engine::Instance()->GetDeltaTime() * speed * direction.y;

		// Destroy obstacle if is really far from player

		if (glm::distance(position, player->GetPosition()) > distance_from_player) {
			Engine::Instance()->DestroyObject(this);
		}
	}
}