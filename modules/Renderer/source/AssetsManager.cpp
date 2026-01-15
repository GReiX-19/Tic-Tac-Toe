#include "AssetsManager.h"

namespace Renderer {

	bool AssetsManager::load_font(const std::string& _name, const std::filesystem::path& _path) {
		auto font = std::make_unique<sf::Font>();
		
		if (!font->openFromFile(_path)) {
			return false;
		}

		m_fonts[_name] = std::move(font);
		return true;
	}

	bool AssetsManager::load_texture(const std::string& _name, const std::filesystem::path& _path) {
		auto texture = std::make_unique<sf::Texture>();
		
		if (!texture->loadFromFile(_path)) {
			return false;
		}

		m_textures[_name] = std::move(texture);
		return true;
	}

	sf::Font& AssetsManager::get_font(const std::string& _name) {
		return *(m_fonts.at(_name));
	}

	sf::Texture& AssetsManager::get_texture(const std::string& _name) {
		return *(m_textures.at(_name));
	}

}