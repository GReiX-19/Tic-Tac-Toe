#include "RenderScreens/MenuScreen.h"

namespace Renderer {
	MenuScreen::MenuScreen(Renderer& _renderer, AssetsManager& _assetsManager)
		: m_renderer(_renderer), m_assetsManager(_assetsManager), m_textRenderer(_assetsManager)
		, m_playButton(_assetsManager.get_texture("playButton")) {
		m_playButton.setOrigin(m_playButton.getGlobalBounds().getCenter());
		m_playButton.setPosition({ 400.f, 400.f });
	}

	void MenuScreen::handle_event(const sf::Event& _event) {
		if (const auto* mousePos = _event.getIf<sf::Event::MouseMoved>()) {
			if (m_playButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position)))
				m_playButton.setTexture(m_assetsManager.get_texture("playButtonHovered"));
		}

		if (const auto* mousePos = _event.getIf<sf::Event::MouseButtonPressed>()) {
			if (mousePos->button == sf::Mouse::Button::Left) {
				if (m_playButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position))) {
					m_playButton.setTexture(m_assetsManager.get_texture("playButton"));
				}
			}
		}
		else if (const auto* mousePos = _event.getIf<sf::Event::MouseButtonReleased>()) {
			if (mousePos->button == sf::Mouse::Button::Left) {
				if (m_playButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position))) {
					m_renderer.switch_state(AppState::Game);
				}
			}
		}

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
		_window.draw(m_playButton);
	}
} 