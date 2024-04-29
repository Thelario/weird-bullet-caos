#include "Asteroid.h"

#include "../Engine/LoggerManager.h"
#include "../Engine/Engine.h"

namespace BulletGame
{
	const float distance_from_player = 2200;

	Asteroid::Asteroid(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable, bool collidable,
		glm::vec2 size, glm::vec2 offset, ColliderTag tag, float speed, glm::vec2 direction, GameObject* player)
		: GameObject(position, scale, rotation, texture_id, width, height, flip_x, tile_id, center_aligned, z_index, color, enabled,
		renderable, collidable, size, offset, tag), speed(speed), direction(direction), player(player)
	{ }

	void Asteroid::Start()
	{
		GameObject::Start();

		animation_rate = 0.5;
		min_size = glm::vec2(scale.x * 0.9, scale.y * 0.9);
		max_size = glm::vec2(scale.x * 1.10, scale.y * 1.10);
	}

	void Asteroid::Update()
	{
		double dt = Engine::Instance()->GetDeltaTime();

		// Move obstacle

		position.x += dt * speed * direction.x;
		position.y += dt * speed * direction.y;

		// Animated obstacle

		scale.x += dt * animation_rate;
		scale.y += dt * animation_rate;

		if ((scale.x >= max_size.x && scale.y >= max_size.y) || (scale.x <= min_size.x && scale.y <= min_size.y)) {
			animation_rate *= -1;
		}

		// Destroy obstacle if is really far from player

		if (glm::distance(position, player->GetPosition()) > distance_from_player) {
			Engine::Instance()->DestroyObject(this);
		}
	}

	void Asteroid::OnCollisionEnter(GameObject* other)
	{
		if (other->CompareTag(ColliderTag::BULLET))
		{
			Engine::Instance()->DestroyObject(this);
		}
	}
}