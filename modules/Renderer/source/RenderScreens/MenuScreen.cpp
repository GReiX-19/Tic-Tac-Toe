#include "RenderScreens/MenuScreen.h"
#include "Renderer.h"
#include "AssetsManager.h"

namespace Renderer {
	MenuScreen::MenuScreen(Renderer& _renderer, AssetsManager& _assetsManager)
		: m_renderer(_renderer), m_assetsManager(_assetsManager), m_textRenderer(_assetsManager)
		, m_playButton(_assetsManager.get_texture("playButton"))
		, m_exitButton(_assetsManager.get_texture("exitButton")) {
		m_playButton.setOrigin(m_playButton.getGlobalBounds().getCenter());
		m_playButton.setPosition({ 300.f, 350.f });
		m_exitButton.setOrigin(m_exitButton.getGlobalBounds().getCenter());
		m_exitButton.setPosition({ 300.f, 450.f });
	}

	void MenuScreen::handle_event(const sf::Event& _event) {
		if (const auto* mousePos = _event.getIf<sf::Event::MouseMoved>()) {
			//Hover effect for play button
			if (m_playButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position)))
				m_playButton.setTexture(m_assetsManager.get_texture("playButtonHovered"));
			else 
				m_playButton.setTexture(m_assetsManager.get_texture("playButton"));

			//Hover effect for exit button
			if (m_exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position)))
				m_exitButton.setTexture(m_assetsManager.get_texture("exitButtonHovered"));
			else 
				m_exitButton.setTexture(m_assetsManager.get_texture("exitButton"));
		}

		if (const auto* mousePos = _event.getIf<sf::Event::MouseButtonPressed>()) {
			if (mousePos->button == sf::Mouse::Button::Left) {
				// Click effect for play button
				if (m_playButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position))) {
					m_playButton.setTexture(m_assetsManager.get_texture("playButton"));
				}
				// Click effect for exit button
				if (m_exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position))) {
					m_exitButton.setTexture(m_assetsManager.get_texture("exitButton"));
				}
			}
		}
		else if (const auto* mousePos = _event.getIf<sf::Event::MouseButtonReleased>()) {
			if (mousePos->button == sf::Mouse::Button::Left) {
				// Switch to game state if play button is clicked
				if (m_playButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position))) {
					m_renderer.switch_state(AppState::Game);
				}
				// Exit application if exit button is clicked
				if (m_exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position))) {
					m_renderer.switch_state(AppState::Exit);
				}
			}
		}

		if (const auto* key = _event.getIf<sf::Event::KeyPressed>()) {
			if (key->scancode == sf::Keyboard::Scan::Enter) {
				m_renderer.switch_state(AppState::Game);
			}
			if (key->scancode == sf::Keyboard::Scan::Escape) {
				m_renderer.switch_state(AppState::Exit);
			}
		}
	}

	void MenuScreen::update(float _dt) {
		// No update logic needed for the menu screen
	}

	void MenuScreen::draw(sf::RenderWindow& _window) {
		m_textRenderer.draw_centered_text(_window, "Welcome to Tic Tac Toe Game!", 40, sf::Color::White, (_window.getSize().y / 2.0f) - 100.f);
		_window.draw(m_playButton);
		_window.draw(m_exitButton);
	}
} 