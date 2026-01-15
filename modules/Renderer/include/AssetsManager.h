#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include <SFML/Graphics.hpp>

namespace Renderer {
	class AssetsManager {
	public:

		AssetsManager() = default;

		bool load_font(const std::string& _name, const std::filesystem::path& _path);
		bool load_texture(const std::string& _name, const std::filesystem::path& _path);

		sf::Font& get_font(const std::string& _name);
		sf::Texture& get_texture(const std::string& _name);

	private:
		std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fonts;
		std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
	};
}