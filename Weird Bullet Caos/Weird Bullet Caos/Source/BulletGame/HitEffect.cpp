#include "HitEffect.h"

#include "../Engine/Engine.h"

namespace BulletGame
{
	HitEffect::HitEffect(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable, bool collidable,
		glm::vec2 size, glm::vec2 offset, ColliderTag tag) : GameObject(position, scale, rotation, texture_id, width, height, flip_x,
		tile_id, center_aligned, z_index, color, enabled, renderable, collidable, size, offset, tag)
	{ }

	void HitEffect::Start()
	{
		time_to_destroy = 200;
		time_to_destroy_counter = SDL_GetTicks();
	}

	void HitEffect::Update()
	{
		if (SDL_GetTicks() - time_to_destroy_counter >= time_to_destroy) {
			Engine::Instance()->DestroyObject(this);
		}
	}
}