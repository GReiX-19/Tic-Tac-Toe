#pragma once
#include <string_view>

namespace sf {
	class RenderWindow;
	class Color;
}

class AssetsManager;

namespace Renderer {
	class TextRenderer {
	public:

		TextRenderer(AssetsManager& _assetsManager);

		void draw_text(sf::RenderWindow& _window, std::string_view _text, const size_t& _charSize,
			const sf::Color& _color, const float& _x, const float& _y);
		void draw_centered_text(sf::RenderWindow& _window, std::string_view _text, const size_t& _charSize,
			const sf::Color& _color, const float& _y);

	private:
		AssetsManager& m_assetsManager;
	};
}