#include "FontsManager.h"

#include "LoggerManager.h"

namespace Satellite
{
	FontsManager* FontsManager::Instance()
	{
		static FontsManager* instance = new FontsManager();
		return instance;
	}

	bool FontsManager::Start()
	{
		bool success = false;

		// Loading fonts

		success = AddFont("arial-font", "./Assets/Fonts/arial.ttf", 100);
		success = AddFont("charriot-font", "./Assets/Fonts/charriot.ttf", 100);

		return success;
	}

	void FontsManager::Destroy()
	{
		for (auto font : _fonts) {
			TTF_CloseFont(font.second);
		}

		_fonts.clear();
	}

	bool FontsManager::AddFont(const std::string& asset_id, const std::string& file_path, int font_size)
	{
		TTF_Font* font = TTF_OpenFont(file_path.c_str(), font_size);

		if (font == NULL) {
			LoggerManager::Error("A problem occure when opening font with " + asset_id, TTF_GetError());
			return false;
		}

		_fonts.emplace(asset_id, font);
	}

	TTF_Font* FontsManager::GetFont(const std::string& asset_id) const
	{
		if (_fonts.find(asset_id) == _fonts.end()) {
			LoggerManager::Error("Trying to get a font with a wrong asset id: " + asset_id);
			return nullptr;
		}

		return _fonts.at(asset_id);
	}
}