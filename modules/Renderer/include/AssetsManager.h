#pragma once
#include <string_view>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Renderer {
	class AssetsManager {
	public:

		AssetsManager() = default;

		bool load_font(std::string_view _name, const std::filesystem::path& _path);
		bool load_texture(std::string_view _name, const std::filesystem::path& _path);

		sf::Font& get_font(std::string_view _name);
		sf::Texture& get_texture(std::string_view _name);

	private:
		std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fonts;
		std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
	};
}