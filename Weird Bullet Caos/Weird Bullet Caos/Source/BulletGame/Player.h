#pragma once

#include "../Engine/GameObject.h"

using namespace Satellite;

namespace BulletGame
{
	class Player : public GameObject
	{
	private:
		glm::vec2 limits[4];
		glm::vec2 direction;
		int current_limit;
		float error;
		float speed;

	public:
		Player(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
			bool flip_x, int tile_id = -1, bool center_aligned = true, int z_index = 0, SDL_Color color = { 255, 255, 255, 255 });

		void Start() override;
		void Update() override;
	};
}