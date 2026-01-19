#include "TextRenderer.h"
#include <SFML/Graphics/Text.hpp>
#include "AssetsManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace Renderer {
	TextRenderer::TextRenderer(AssetsManager& _assetsManager)
		: m_assetsManager(_assetsManager) {
	}

	void TextRenderer::draw_centered_text(sf::RenderWindow& _window, std::string_view _text,
		const size_t& _charSize, const sf::Color& _color, const float& _y) {
		sf::Text text(m_assetsManager.get_font("mainFont"), sf::String(_text.data()), _charSize);
		text.setFillColor(_color);
		text.setOutlineThickness(2.f);
		text.setOutlineColor(sf::Color::Black);

		sf::FloatRect textBounds = text.getLocalBounds();
		text.setOrigin({ textBounds.getCenter().x, textBounds.getCenter().y });
		text.setPosition({ _window.getSize().x / 2.f, _y });

		_window.draw(text);
	}
}