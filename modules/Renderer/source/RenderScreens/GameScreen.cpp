#include "RenderScreens/GameScreen.h"
#include "Renderer.h"
#include "GameState.h"
#include "AssetsManager.h"
#include <SFML/Graphics/Sprite.hpp>

namespace Renderer {
	GameScreen::GameScreen(Renderer& _renderer, AssetsManager& _assetsManager, EngineCore::GameState& _gameState)
		: m_renderer(_renderer)
		, m_assetsManager(_assetsManager)
		, m_gameState(_gameState)
		, m_textRenderer(_assetsManager)
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
				m_gameState.make_move({m_keyboardCursorPos.x, m_keyboardCursorPos.y});
				break;
			}
		}

		if (const auto* mouse = _event.getIf<sf::Event::MouseButtonPressed>()) {
			if (mouse->button == sf::Mouse::Button::Left) {
				const sf::Vector2i gridPos = { m_mousePosition.x / 200, m_mousePosition.y / 200 };
				if (gridPos.y <= 2)
					m_gameState.make_move({ gridPos.x, gridPos.y });
			}
		}
	}

	void GameScreen::update(float _dt) {
		if (m_gameState.is_win(EngineCore::PlayerMark::PLAYER_X)) {
			m_gameState.add_crossWin();
			m_renderer.switch_state(AppState::GameOver);
		}
		else if (m_gameState.is_win(EngineCore::PlayerMark::PLAYER_O)) {
			m_gameState.add_circleWin();
			m_renderer.switch_state(AppState::GameOver);
		}
		else if (m_gameState.is_draw()) {
			m_renderer.switch_state(AppState::GameOver);
		}
	}

	void GameScreen::draw(sf::RenderWindow& _window) {
		sf::Sprite crossWins(m_assetsManager.get_texture("crossTexture"));
		sf::Sprite circleWins(m_assetsManager.get_texture("circleTexture"));

		crossWins.setOrigin(crossWins.getGlobalBounds().getCenter());
		crossWins.scale({ 0.3f, 0.3f });
		crossWins.setPosition({ (_window.getSize().x / 2) - 50.f, 630.f});

		circleWins.setOrigin(circleWins.getGlobalBounds().getCenter());
		circleWins.scale({ 0.3f, 0.3f });
		circleWins.setPosition({ (_window.getSize().x / 2) + 50.f, 630.f });

		m_boardView.draw(_window, m_mousePosition, m_keyboardCursorPos, m_isUsingKeyboard);

		_window.draw(crossWins);
		_window.draw(circleWins);

		m_textRenderer.draw_text(_window, std::to_string(m_gameState.get_crossWins()), 30, sf::Color::White, (_window.getSize().x / 2) - 50.f, 670.f);
		m_textRenderer.draw_text(_window, std::to_string(m_gameState.get_circleWins()), 30, sf::Color::White, (_window.getSize().x / 2) + 50.f, 670.f);
	}
}