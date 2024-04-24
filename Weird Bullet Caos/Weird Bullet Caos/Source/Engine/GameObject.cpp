#include "GameObject.h"

#include "Engine.h"
#include "LoggerManager.h"

namespace Satellite
{
	GameObject::GameObject(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& texture_id, int width, int height,
		bool flip_x, int tile_id, bool center_aligned, int z_index, SDL_Color color)
		: position(position), scale(scale), rotation(rotation), texture_id(texture_id), width(width), height(height),
		flip_x(flip_x), tile_id(tile_id), center_aligned(center_aligned), z_index(z_index), color(color), enabled(true)
	{ }

	void GameObject::Start() {
		SetColor(color);
	}

	void GameObject::Update() { }

	void GameObject::Render()
	{
		// Generate source rect with the given texture.
		Texture* texture = TexturesManager::Instance()->GetTexture(texture_id);
		SDL_Rect src;
		src = (tile_id == -1) ? (texture->GetSourceRect()) : (texture->GetTileSourceRect(tile_id));

		// Calculate real width and height based on scale.
		float real_width = width * scale.x;
		float real_height = height * scale.y;

		// Calculate correct position based on center alignment.
		int pos_x = (center_aligned) ? (static_cast<int>(position.x - (real_width / 2))) : (position.x);
		int pos_y = (center_aligned) ? (static_cast<int>(position.y - (real_height / 2))) : (position.y);

		// Creating the destination rectangle.
		SDL_Rect dest = {
			static_cast<int>(pos_x),
			static_cast<int>(pos_y),
			static_cast<int>(real_width),
			static_cast<int>(real_height)
		};

		// Rendering based on the flip and rotation provided.
		
		SDL_RendererFlip flip = flip_x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		SDL_RenderCopyEx(Engine::Instance()->GetRenderer(), texture->GetTexture(), &src, &dest, rotation, NULL, flip);
	}

	void GameObject::SetColor(SDL_Color color) {
		Texture* texture = TexturesManager::Instance()->GetTexture(texture_id);
		if (SDL_SetTextureColorMod(texture->GetTexture(), color.r, color.g, color.b) != 0) {
			LoggerManager::Error("A problem occured when setting the color for " + texture_id, SDL_GetError());
		}
	}

	void GameObject::Enable(bool enabled) { this->enabled = enabled; }
	void GameObject::SetPosition(glm::vec2 position) { this->position = position; }
	void GameObject::SetRotation(double rotation) { this->rotation = rotation; }
}