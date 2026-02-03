#include "RenderScreens/GameOverScreen.h"
#include "GameState.h"
#include "Renderer.h"
#include "AssetsManager.h"

namespace Renderer {
	GameOverScreen::GameOverScreen(Renderer& _renderer, AssetsManager& _assetsManager, EngineCore::GameState& _state)
		: m_renderer(_renderer)
		, m_assetsManager(_assetsManager)
		, m_gameState(_state)
		, m_textRenderer(_assetsManager)
		, m_boardView(_state, _assetsManager) 
		, m_restartButton(_assetsManager.get_texture("restartButton"))
		, m_menuButton(_assetsManager.get_texture("menuButton")) {
		m_restartButton.setOrigin(m_restartButton.getGlobalBounds().getCenter());
		m_restartButton.setPosition({ 200.f, 350.f });
		m_menuButton.setOrigin(m_menuButton.getGlobalBounds().getCenter());
		m_menuButton.setPosition({ 400.f, 350.f });
	}

	void GameOverScreen::handle_event(const sf::Event& _event) {
		if (const auto* mousePos = _event.getIf<sf::Event::MouseMoved>()) {
			//Hover effect for play button
			if (m_restartButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position)))
				m_restartButton.setTexture(m_assetsManager.get_texture("restartButtonHovered"));
			else
				m_restartButton.setTexture(m_assetsManager.get_texture("restartButton"));

			//Hover effect for exit button
			if (m_menuButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position)))
				m_menuButton.setTexture(m_assetsManager.get_texture("menuButtonHovered"));
			else
				m_menuButton.setTexture(m_assetsManager.get_texture("menuButton"));
		}

		if (const auto* mousePos = _event.getIf<sf::Event::MouseButtonPressed>()) {
			if (mousePos->button == sf::Mouse::Button::Left) {
				// Click effect for play button
				if (m_restartButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position))) {
					m_restartButton.setTexture(m_assetsManager.get_texture("restartButton"));
				}
				// Click effect for exit button
				if (m_menuButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position))) {
					m_menuButton.setTexture(m_assetsManager.get_texture("menuButton"));
				}
			}
		}
		else if (const auto* mousePos = _event.getIf<sf::Event::MouseButtonReleased>()) {
			if (mousePos->button == sf::Mouse::Button::Left) {
				// Switch to game state if play button is clicked
				if (m_restartButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position))) {
					m_gameState.reset();
					m_renderer.switch_state(AppState::Game);
				}
				// Exit application if exit button is clicked
				if (m_menuButton.getGlobalBounds().contains(sf::Vector2f(mousePos->position))) {
					m_gameState.reset();
					m_gameState.reset_wins();
					m_renderer.switch_state(AppState::Menu);
				}
			}
		}

		if (const auto* key = _event.getIf<sf::Event::KeyPressed>()) {
			if (key->scancode == sf::Keyboard::Scan::Enter) {
				m_gameState.reset();
				m_renderer.switch_state(AppState::Game);
			}
			if (key->scancode == sf::Keyboard::Scan::Escape) {
				m_gameState.reset();
				m_gameState.reset_wins();
				m_renderer.switch_state(AppState::Menu);
			}
		}
	}

	void GameOverScreen::update(float _dt) {
		// No update logic needed for the game over screen
	}

	void GameOverScreen::draw(sf::RenderWindow& _window) {
		sf::Sprite crossWins(m_assetsManager.get_texture("crossTexture"));
		sf::Sprite circleWins(m_assetsManager.get_texture("circleTexture"));

		crossWins.setOrigin(crossWins.getGlobalBounds().getCenter());
		crossWins.scale({ 0.3f, 0.3f });
		crossWins.setPosition({ (_window.getSize().x / 2) - 50.f, 630.f });

		circleWins.setOrigin(circleWins.getGlobalBounds().getCenter());
		circleWins.scale({ 0.3f, 0.3f });
		circleWins.setPosition({ (_window.getSize().x / 2) + 50.f, 630.f });

		m_boardView.draw_board(_window);
		m_boardView.draw_marks(_window);
		m_boardView.draw_win_line(_window);
		
		if (m_gameState.is_win(EngineCore::Player::PLAYER_X)) {
			m_textRenderer.draw_centered_text(_window, "Player X Wins!", 80, sf::Color::White, ((_window.getSize().y / 2.f) - 60.f));
		}
		else if (m_gameState.is_win(EngineCore::Player::PLAYER_O)) {
			m_textRenderer.draw_centered_text(_window, "Player O Wins!", 80, sf::Color::White, ((_window.getSize().y / 2.f) - 60.f));
		}
		else if (m_gameState.is_draw()) {
			m_textRenderer.draw_centered_text(_window, "It's a Draw!", 80, sf::Color::White, ((_window.getSize().y / 2.f) - 60.f));
		}

		_window.draw(crossWins);
		_window.draw(circleWins);

		m_textRenderer.draw_text(_window, std::to_string(m_gameState.get_crossWins()), 30, sf::Color::White, (_window.getSize().x / 2) - 50.f, 670.f);
		m_textRenderer.draw_text(_window, std::to_string(m_gameState.get_circleWins()), 30, sf::Color::White, (_window.getSize().x / 2) + 50.f, 670.f);
		
		_window.draw(m_restartButton);
		_window.draw(m_menuButton);
	}
}