#include "GameScreen.h"

namespace Renderer {
	GameScreen::GameScreen(Renderer& _renderer, AssetsManager& _assetsManager, EngineCore::GameState& _state)
		: m_renderer(_renderer)
		, m_assetsManager(_assetsManager)
		, m_gameState(_state)
		, m_boardView(m_gameState, _assetsManager) {
	}

	void GameScreen::handle_event(const sf::Event& _event) {
		if (const auto* key = _event.getIf<sf::Event::KeyPressed>()) {
			if (key->scancode == sf::Keyboard::Scan::Escape) {
				m_renderer.switch_state(AppState::Menu);
			}
		}

		if (const auto* mouseMove = _event.getIf<sf::Event::MouseMoved>()) {
			m_isUsingKeyboard = false;
			m_mousePosition = { mouseMove->position.x, mouseMove->position.y };
		}
		if (const auto* keyboard = _event.getIf<sf::Event::KeyPressed>()) {
			m_isUsingKeyboard = true;

			switch (keyboard->scancode) {
			case sf::Keyboard::Scan::Up:
			case sf::Keyboard::Scan::W:
				if (m_keyboardCursorPos.y > 0)
					m_keyboardCursorPos.y--;
				break;
			case sf::Keyboard::Scan::Down:
			case sf::Keyboard::Scan::S:
				if (m_keyboardCursorPos.y < 2)
					m_keyboardCursorPos.y++;
				break;
			case sf::Keyboard::Scan::Left:
			case sf::Keyboard::Scan::A:
				if (m_keyboardCursorPos.x > 0)
					m_keyboardCursorPos.x--;
				break;
			case sf::Keyboard::Scan::Right:
			case sf::Keyboard::Scan::D:
				if (m_keyboardCursorPos.x < 2)
					m_keyboardCursorPos.x++;
				break;
			case sf::Keyboard::Scan::Enter:
				m_gameState.make_move(m_keyboardCursorPos.x, m_keyboardCursorPos.y);
				break;
			}
		}

		if (const auto* mouse = _event.getIf<sf::Event::MouseButtonPressed>()) {
			if (mouse->button == sf::Mouse::Button::Left) {
				const sf::Vector2i gridPos = { m_mousePosition.x / 200, m_mousePosition.y / 200 };
				m_gameState.make_move(gridPos.x, gridPos.y);
			}
		}
	}

	void GameScreen::update(float _dt) {
		if (m_gameState.is_win(EngineCore::Player::PLAYER_X)) {
			m_winner = EngineCore::Player::PLAYER_X;
			m_renderer.switch_state(AppState::GameOver);
		}
		else if (m_gameState.is_win(EngineCore::Player::PLAYER_O)) {
			m_winner = EngineCore::Player::PLAYER_O;
			m_renderer.switch_state(AppState::GameOver);
		}
		else if (m_gameState.is_draw()) {
			m_renderer.switch_state(AppState::GameOver);
		}
	}

	void GameScreen::draw(sf::RenderWindow& _window) {
		m_boardView.draw(_window, m_mousePosition, m_keyboardCursorPos, m_isUsingKeyboard);
	}
}