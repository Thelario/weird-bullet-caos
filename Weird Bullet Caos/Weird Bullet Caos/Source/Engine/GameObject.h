#pragma once

#include <glm/glm.hpp>
#include <string>
#include <SDL.h>

#include "TexturesManager.h"

namespace Satellite
{
	class GameObject
	{
	protected:

		// Transform data

		glm::vec2 position;
		glm::vec2 scale;
		double rotation;

		// Sprite data

		std::string texture_id;
		int width;
		int height;
		int z_index;
		int tile_id;
		bool flip_x;
		bool center_aligned;
		SDL_Color color;

	public:
		GameObject(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
			bool flip_x, bool center_aligned = true, int z_index = 0, int tile_id = -1, SDL_Color color = { 255, 255, 255, 255 });

		virtual void Start();
		virtual void Update();
		virtual void Render();

		void SetPosition(glm::vec2 position);
		void SetRotation(double rotation);
	};
}