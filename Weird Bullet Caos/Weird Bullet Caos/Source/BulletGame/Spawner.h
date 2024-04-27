#pragma once

#include "../Engine/GameObject.h"

using namespace Satellite;

namespace BulletGame
{
	struct ObstacleInfo
	{
		std::string id;
		glm::vec2 collider_size;
	};

	class Spawner : public GameObject
	{
	private:
		ObstacleInfo obstacles[4];

		float obstacles_speed;
		float spawn_distance_from_center;
		Uint32 previous_time_between_obstacles;
		Uint32 time_between_obstacles;

		GameObject* player;

	public:
		Spawner(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
			bool flip_x, int tile_id = -1, bool center_aligned = true, int z_index = 0, SDL_Color color = { 255, 255, 255, 255 },
			bool enabled = true, bool renderable = true, GameObject* player = nullptr);

		void Start() override;
		void Update() override;
	};
}