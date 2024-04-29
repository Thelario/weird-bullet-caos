#include "Bullet.h"

#include "../Engine/SoundsManager.h"
#include "../Engine/Engine.h"

#include "HitEffect.h"
#include "BulletGame.h"

namespace BulletGame
{
	Bullet::Bullet(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable, bool collidable,
		glm::vec2 size, glm::vec2 offset, ColliderTag tag, float speed, glm::vec2 direction, BulletGame* bullet_game)
		: GameObject(position, scale, rotation, texture_id, width, height, flip_x, tile_id, center_aligned, z_index, color, enabled,
			renderable, collidable, size, offset, tag), speed(speed), direction(direction), bullet_game(bullet_game)
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
			glm::vec2 hit_effect_pos = glm::vec2(
				(other->GetPosition().x - position.x) / 2 + position.x,
				(other->GetPosition().y - position.y) / 2 + position.y);

			double random_angle = Engine::Instance()->GetRandom()->GenerateRandomFloat(0, 360);

			Engine::Instance()->CreateObject(new HitEffect(hit_effect_pos, glm::vec2(Engine::Instance()->GetRandom()->GenerateRandomFloat(1.5, 3)),
				random_angle, "basic-shapes", 32, 32, false, 1));

			bullet_game->ScoreUp();
			SoundsManager::Instance()->PlaySound("asteroid-hit");
			Engine::Instance()->DestroyObject(this);
		}
	}
}