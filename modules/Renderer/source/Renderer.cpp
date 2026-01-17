#include "Renderer.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include <SFML/Window/Event.hpp>

namespace Renderer {

	Renderer::Renderer(EngineCore::GameState& _gameState)
		: m_gameState(_gameState)
		, m_appState(AppState::Menu)
		, m_window(sf::VideoMode({ 600, 600 }), "Tic Tac Toe", sf::Style::Titlebar | sf::Style::Close)
		, m_textRenderer(m_assetsManager)
		, m_assetsManager() {
		m_window.setFramerateLimit(60);

		if (!m_assetsManager.load_font("mainFont", "Assets/Tuffy.ttf")
			or !m_assetsManager.load_texture("boardTexture", "Assets/board.png")
			or !m_assetsManager.load_texture("circleTexture", "Assets/circle.png")
			or !m_assetsManager.load_texture("crossTexture", "Assets/cross.png")) {
			throw std::runtime_error("Failed to load assets");
		}
	}

	void Renderer::run() {
		switch_state(AppState::Menu);

		sf::Clock clock;

		while (m_window.isOpen()) {
			while (const std::optional event = m_window.pollEvent()) {

				if (event->is<sf::Event::Closed>()) {
					m_window.close();
				}
				else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
					if (key->scancode == sf::Keyboard::Scan::Escape) {
						m_window.close();
					}
				}
				m_currentScreen->handle_event(event.value());

			}

			const float dt = clock.restart().asSeconds();
			m_currentScreen->update(dt);

			m_currentScreen->draw(m_window);
			m_window.display();
		}
	}

	/*void Renderer::processEvents() {
		while (const std::optional event = m_window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				m_window.close();
			}
			else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
				if (key->scancode == sf::Keyboard::Scan::Escape) {
					m_window.close();
				}
			}

			if (m_renderState == RenderState::GameOver) {
				if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
					if (key->scancode == sf::Keyboard::Scan::Enter) {
						m_gameState.reset();
						m_renderState = RenderState::Playing;
					}
				}
			}
			else {
				if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>()) {
					m_isUsingKeyboard = false;
					m_mousePosition = { mouseMove->position.x, mouseMove->position.y };
				}
				if (const auto* keyboard = event->getIf<sf::Event::KeyPressed>()) {
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

				if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
					if (mouse->button == sf::Mouse::Button::Left) {
						const sf::Vector2i gridPos = { m_mousePosition.x / 200, m_mousePosition.y / 200 };
						m_gameState.make_move(gridPos.x, gridPos.y);
					}
				}
			}
		}
	}

	void Renderer::update() {
		if (m_renderState == RenderState::GameOver) {
			return;
		}
		if (m_gameState.is_win(EngineCore::Player::PLAYER_X)) {
			m_renderState = RenderState::GameOver;
			m_winner = EngineCore::Player::PLAYER_X;
		}
		else if (m_gameState.is_win(EngineCore::Player::PLAYER_O)) {
			m_renderState = RenderState::GameOver;
			m_winner = EngineCore::Player::PLAYER_O;
		}
		else if (m_gameState.is_draw()) {
			m_renderState = RenderState::GameOver;
		}
	}

	void Renderer::render(BoardView& _boardView) {
		m_window.clear(sf::Color::Black);

		_boardView.draw(m_window, m_mousePosition, m_keyboardCursorPos, m_isUsingKeyboard);

		if (m_renderState == RenderState::GameOver) {
			if (m_gameState.is_draw()) {
				m_textRenderer.draw_game_over_text(m_window, "It's a Draw!");
			}
			else if (m_winner == EngineCore::Player::PLAYER_X) {
				m_textRenderer.draw_game_over_text(m_window, "Player X Wins!");
			}
			else if (m_winner == EngineCore::Player::PLAYER_O) {
				m_textRenderer.draw_game_over_text(m_window, "Player O Wins!");
			}
		}

		m_window.display();
	}*/

	void Renderer::switch_state(AppState _newState) {
		m_appState = _newState;

		switch (_newState) {
		case AppState::Menu:
			m_currentScreen = std::make_unique<MenuScreen>(*this, m_assetsManager);
			break;
		case AppState::Game:
			m_currentScreen = std::make_unique<GameScreen>(*this, m_assetsManager, m_gameState);
			break;
		case AppState::GameOver:
			m_currentScreen = std::make_unique<GameOverScreen>(*this, m_assetsManager, m_gameState);
			break;
		}
	}

}