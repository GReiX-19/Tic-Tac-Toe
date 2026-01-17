#include "TextRenderer.h"

namespace Renderer {
	TextRenderer::TextRenderer(AssetsManager& _assetsManager)
		: m_assetsManager(_assetsManager) {
	}

	void TextRenderer::draw_centered_text(sf::RenderWindow& _window, std::string_view _text,
		const size_t _charSize, const sf::Color& _color, const float _y) {
		sf::Text text(m_assetsManager.get_font("mainFont"), sf::String(_text.data()), _charSize);
		text.setFillColor(_color);
		text.setOutlineThickness(2.f);
		text.setOutlineColor(sf::Color::Black);

		sf::FloatRect textBounds = text.getLocalBounds();
		text.setOrigin({ textBounds.getCenter().x, textBounds.getCenter().y });
		text.setPosition({ _window.getSize().x / 2.f, _y });

		_window.draw(text);
	}

	void TextRenderer::draw_game_over_text(sf::RenderWindow& _window, std::string_view _text) {
		const float yPosition = _window.getSize().y / 2.f;
		draw_centered_text(_window, _text, 80, sf::Color::White, yPosition);
		draw_centered_text(_window, "Press Enter to Restart", 50, sf::Color::White, yPosition + 80.f);
		draw_centered_text(_window, "Or Press Escape to Exit to the Main Menu", 30, sf::Color::White, yPosition + 150.f);
	}
}