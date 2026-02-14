#include "AssetsManager.h"

AssetsManager::AssetsManager() {
	if (!load_font("mainFont", "Assets/AveriaGruesaLibre-Regular.ttf")
		or !load_texture("boardTexture", "Assets/board.png")
		or !load_texture("circleTexture", "Assets/circle.png")
		or !load_texture("crossTexture", "Assets/cross.png")
		or !load_texture("playButton", "Assets/buttons/playButton.png")
		or !load_texture("playButtonHovered", "Assets/buttons/playButtonHovered.png")
		or !load_texture("exitButton", "Assets/buttons/exitButton.png")
		or !load_texture("exitButtonHovered", "Assets/buttons/exitButtonHovered.png")
		or !load_texture("restartButton", "Assets/buttons/restartButton.png")
		or !load_texture("restartButtonHovered", "Assets/buttons/restartButtonHovered.png")
		or !load_texture("menuButton", "Assets/buttons/menuButton.png")
		or !load_texture("menuButtonHovered", "Assets/buttons/menuButtonHovered.png")
		or !load_texture("gameIcon", "Assets/gameIcon.png")
		or !load_texture("vsBotButton", "Assets/buttons/vsBotButton.png")
		or !load_texture("vsBotButtonHovered", "Assets/buttons/vsBotButtonHovered.png")
		or !load_texture("vsBotButtonMarked", "Assets/buttons/vsBotButtonMarked.png")
		or !load_texture("vsBotButtonHoveredMarked", "Assets/buttons/vsBotButtonHoveredMarked.png")) {
		throw std::runtime_error("Failed to load assets");
	}
}

bool AssetsManager::load_font(std::string_view _name, const std::filesystem::path& _path) {
	auto font = std::make_unique<sf::Font>();

	if (!font->openFromFile(_path)) {
		return false;
	}

	m_fonts[_name.data()] = std::move(font);
	return true;
}

bool AssetsManager::load_texture(std::string_view _name, const std::filesystem::path& _path) {
	auto texture = std::make_unique<sf::Texture>();

	if (!texture->loadFromFile(_path)) {
		return false;
	}

	m_textures[_name.data()] = std::move(texture);
	return true;
}

sf::Font& AssetsManager::get_font(std::string_view _name) {
	return *(m_fonts.at(_name.data()));
}

sf::Texture& AssetsManager::get_texture(std::string_view _name) {
	return *(m_textures.at(_name.data()));
}