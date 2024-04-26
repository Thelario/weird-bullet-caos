#pragma once

#include <glm/glm.hpp>
#include <string>
#include <SDL.h>

#include "TexturesManager.h"

namespace Satellite
{
	class GameObject
	{
	public:
		bool enabled = true;
		bool renderable = true;

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
			bool flip_x, int tile_id = -1, bool center_aligned = true, int z_index = 0, SDL_Color color = { 255, 255, 255, 255 },
			bool enabled = true, bool renderable = true);

		virtual void Start();
		virtual void Update();
		void Render();

		void Enable(bool enabled);
		void Renderable(bool renderable);
		void SetColor(SDL_Color color);
		void SetPosition(glm::vec2 position);
		void SetRotation(double rotation);
	};
}