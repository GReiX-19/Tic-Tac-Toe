#include "RenderScreens/GameOverScreen.h"

namespace Renderer {
	GameOverScreen::GameOverScreen(Renderer& _renderer, AssetsManager& _assetsManager, EngineCore::GameState& _state)
		: m_renderer(_renderer)
		, m_assetsManager(_assetsManager)
		, m_gameState(_state)
		, m_textRenderer(_assetsManager)
		, m_boardView(_state, _assetsManager) {
	}

	void GameOverScreen::handle_event(const sf::Event& _event) {
		if (const auto* key = _event.getIf<sf::Event::KeyPressed>()) {
			if (key->scancode == sf::Keyboard::Scan::Enter) {
				m_gameState.reset();
				m_renderer.switch_state(AppState::Game);
			}
		}
	}

	void GameOverScreen::update(float _dt) {
		// No update logic needed for the game over screen
	}

	void GameOverScreen::draw(sf::RenderWindow& _window) {
		m_boardView.draw_board(_window);
		m_boardView.draw_marks(_window);
		m_boardView.draw_win_line(_window);
		
		if (m_gameState.get_winner() == EngineCore::Player::PLAYER_X) {
			m_textRenderer.draw_game_over_text(_window, "Player X Wins!");
		}
		else if (m_gameState.get_winner() == EngineCore::Player::PLAYER_O) {
			m_textRenderer.draw_game_over_text(_window, "Player O Wins!");
		}
		else {
			m_textRenderer.draw_game_over_text(_window, "It's a Draw!");
		}
	}
}