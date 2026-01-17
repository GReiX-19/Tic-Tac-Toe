#include "MenuScreen.h"

namespace Renderer {
	MenuScreen::MenuScreen(Renderer& _renderer, AssetsManager& _assetsManager)
		: m_renderer(_renderer), m_assetsManager(_assetsManager), m_textRenderer(_assetsManager) {
	}

	void MenuScreen::handle_event(const sf::Event& _event) {
		if (const auto* key = _event.getIf<sf::Event::KeyPressed>()) {
			if (key->scancode == sf::Keyboard::Scan::Enter) {
				m_renderer.switch_state(AppState::Game);
			}
		}
	}

	void MenuScreen::update(float _dt) {
		// No update logic needed for the menu screen
	}

	void MenuScreen::draw(sf::RenderWindow& _window) {
		m_textRenderer.draw_centered_text(_window, "Welcome to Tic Tac Toe Game!", 40, sf::Color::White, (_window.getSize().y / 2.0f) - 30.f);
		m_textRenderer.draw_centered_text(_window, "Press Enter to Start", 32, sf::Color::White, (_window.getSize().y / 2.0f) + 30.f);
	}
} 