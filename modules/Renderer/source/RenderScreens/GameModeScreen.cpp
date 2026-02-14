#include "RenderScreens/GameModeScreen.h"
#include "GameState.h"
#include "Renderer.h"
#include "AssetsManager.h"

namespace Renderer {
	GameModeScreen::GameModeScreen(Renderer& _renderer, AssetsManager& _assetsManager, EngineCore::GameState& _gameState)
		: m_renderer(_renderer)
		, m_assetsManager(_assetsManager)
		, m_gameState(_gameState)
		, m_textRenderer(_assetsManager)
		, m_vsBotButton((m_gameState.is_vsBot() == false) ? _assetsManager.get_texture("vsBotButton") : _assetsManager.get_texture("vsBotButtonMarked")) {
		m_vsBotButton.setOrigin(m_vsBotButton.getGlobalBounds().getCenter());
		m_vsBotButton.setScale({ 0.4f, 0.4f });
		m_vsBotButton.setPosition({ 400.f, 350.f });
	}
	
	void GameModeScreen::handle_event(const sf::Event& _event) {
		if (const auto* mousePos = _event.getIf<sf::Event::MouseMoved>()) {
			if (m_gameState.is_vsBot()) {
				if (m_vsBotButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position)))
					m_vsBotButton.setTexture(m_assetsManager.get_texture("vsBotButtonHoveredMarked"));
				else
					m_vsBotButton.setTexture(m_assetsManager.get_texture("vsBotButtonMarked"));
			}
			else {
				if (m_vsBotButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position)))
					m_vsBotButton.setTexture(m_assetsManager.get_texture("vsBotButtonHovered"));
				else
					m_vsBotButton.setTexture(m_assetsManager.get_texture("vsBotButton"));
			}
		}

		if (const auto* mousePos = _event.getIf<sf::Event::MouseButtonPressed>()) {
			if (mousePos->button == sf::Mouse::Button::Left) {
				if (m_gameState.is_vsBot()) {
					if (m_vsBotButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position)))
						m_vsBotButton.setTexture(m_assetsManager.get_texture("vsBotButton"));
					m_gameState.change_vsBot();
				}
				else {
					if (m_vsBotButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position)))
						m_vsBotButton.setTexture(m_assetsManager.get_texture("vsBotButtonMarked"));
					m_gameState.change_vsBot();
				}
			}
		}
		/*else if (const auto* mousePos = _event.getIf<sf::Event::MouseButtonReleased>()) {
			if (mousePos->button == sf::Mouse::Button::Left) {
				if (m_gameState.is_vsBot()) {
					if (m_vsBotButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position)))
						m_vsBotButton.setTexture(m_assetsManager.get_texture("vsBotButtonMarked"));
					m_gameState.change_vsBot();
				}
				else {
					if (m_vsBotButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position)))
						m_vsBotButton.setTexture(m_assetsManager.get_texture("vsBotButton"));
				}
			}
		}*/

		if (const auto* key = _event.getIf<sf::Event::KeyPressed>()) {
			if (key->scancode == sf::Keyboard::Scan::Enter) {
				m_renderer.switch_state(AppState::Game);
			}
			if (key->scancode == sf::Keyboard::Scan::Escape) {
				m_renderer.switch_state(AppState::Menu);
			}
		}
	}
	
	void GameModeScreen::update(float _dt) {
		// No update logic needed for the menu screen
	}

	void GameModeScreen::draw(sf::RenderWindow& _window) {
		m_textRenderer.draw_text(_window, "Change vs Bot:", 40, sf::Color::White, (_window.getSize().x / 2.f) - 60.f, m_vsBotButton.getPosition().y );
		_window.draw(m_vsBotButton);
	}
}