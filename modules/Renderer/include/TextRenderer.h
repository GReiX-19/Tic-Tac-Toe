#pragma once
#include <string_view>

namespace sf {
	class RenderWindow;
	class Color;
}

namespace Renderer {
	class AssetsManager;

	class TextRenderer {
	public:
		TextRenderer(AssetsManager& _assetsManager);

		void draw_centered_text(sf::RenderWindow& _window, std::string_view _text, const size_t& _charSize,
			const sf::Color& _color, const float& _y);
	private:
		AssetsManager& m_assetsManager;
	};
}