#include "Bullet.h"

#include "../Engine/SoundsManager.h"
#include "../Engine/Engine.h"

namespace BulletGame
{
	Bullet::Bullet(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable, bool collidable,
		glm::vec2 size, glm::vec2 offset, ColliderTag tag, float speed, glm::vec2 direction) : GameObject(position, scale, rotation,
		texture_id, width, height, flip_x, tile_id, center_aligned, z_index, color, enabled, renderable, collidable, size, offset,
		tag), speed(speed), direction(direction)
	{ }

	void Bullet::Update()
	{
		// Move bullet

		position.x += Engine::Instance()->GetDeltaTime() * speed * direction.x;
		position.y += Engine::Instance()->GetDeltaTime() * speed * direction.y;

		// Destroy bullet if has reached the borders of the screen

		if (position.x < 0 || position.x > Engine::Instance()->GetWindowWidth() ||
			position.y < 0 || position.y > Engine::Instance()->GetWindowHeight()) {
			Engine::Instance()->DestroyObject(this);
		}
	}

	void Bullet::OnCollisionEnter(GameObject* other)
	{
		if (other->CompareTag(ColliderTag::OBSTACLE) || other->CompareTag(ColliderTag::ENEMY))
		{
			SoundsManager::Instance()->PlaySound("asteroid-hit");
			Engine::Instance()->DestroyObject(this);
		}
	}
}