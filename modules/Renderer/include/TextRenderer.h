#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "AssetsManager.h"

namespace Renderer {
	class TextRenderer {
	public:
		TextRenderer(AssetsManager& _assetsManager);

		void draw_centered_text(sf::RenderWindow& _window, std::string_view _text, const size_t _charSize,
			const sf::Color& _color, const float _y);

		void draw_game_over_text(sf::RenderWindow& _window, std::string_view _text);

	private:
		AssetsManager& m_assetsManager;
	};
}