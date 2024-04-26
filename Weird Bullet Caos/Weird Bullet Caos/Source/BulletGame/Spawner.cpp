#include "Spawner.h"

namespace BulletGame
{
	Spawner::Spawner(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color, bool enabled, bool renderable)
		: GameObject(position, scale, rotation, texture_id, width, height, flip_x, tile_id, center_aligned, z_index, color, enabled, renderable)
	{ }

	void Spawner::Start()
	{
		GameObject::Start();

		spawn_distance_from_center = 500;
	}

	void Spawner::Update()
	{

	}
}