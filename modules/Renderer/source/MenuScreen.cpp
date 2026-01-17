#include "MenuScreen.h"

namespace Renderer {
	MenuScreen::MenuScreen(Renderer& _renderer, AssetsManager& _assetsManager)
		: m_renderer(_renderer), m_assetsManager(_assetsManager)
		, m_titleText(_assetsManager.get_font("mainFont"))
		, m_playButtonText(_assetsManager.get_font("mainFont")) {
		m_titleText.setString("Tic Tac Toe");
		m_titleText.setCharacterSize(64);
		m_titleText.setPosition({ 120.f, 100.f });

		m_playButtonText.setString("Play");
		m_playButtonText.setCharacterSize(48);
		m_playButtonText.setPosition({ 240.f, 300.f });
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
		_window.draw(m_titleText);
		_window.draw(m_playButtonText);
	}
} 