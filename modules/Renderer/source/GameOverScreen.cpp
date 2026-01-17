#include "GameOverScreen.h"

namespace Renderer {
	GameOverScreen::GameOverScreen(Renderer& _renderer, AssetsManager& _assetsManager, EngineCore::GameState& _state)
		: m_renderer(_renderer)
		, m_assetsManager(_assetsManager)
		, m_gameState(_state)
		, m_gameOverText(_assetsManager.get_font("mainFont"))
		, m_restartInstructionText(_assetsManager.get_font("mainFont")) 
		, m_boardView(_state, _assetsManager) {
		if (m_gameState.is_draw()) {
			m_gameOverText.setString("It's a Draw!");
		}
		else if (m_gameState.get_current_player() == EngineCore::Player::PLAYER_X) {
			m_gameOverText.setString("Player X Wins!");
		}
		else {
			m_gameOverText.setString("Player O Wins!");
		}
		m_gameOverText.setCharacterSize(64);
		m_gameOverText.setPosition({ 120.f, 100.f });

		m_restartInstructionText.setString("Press Enter to Restart");
		m_restartInstructionText.setCharacterSize(32);
		m_restartInstructionText.setPosition({ 180.f, 300.f });
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
		_window.draw(m_gameOverText);
		_window.draw(m_restartInstructionText);
	}
}