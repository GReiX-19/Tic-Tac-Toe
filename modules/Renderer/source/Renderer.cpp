#include "Renderer.h"
#include <SFML/Window/Event.hpp>

namespace Renderer {

	Renderer::Renderer(EngineCore::GameState& _gameState)
		: m_gameState(_gameState)
		, m_window(sf::VideoMode({ 600, 600 }), "Tic Tac Toe")
		, m_renderState(RenderState::Playing)
		, m_winner() 
		, m_textRenderer(m_assetsManager) {
		m_window.setFramerateLimit(60);

		if (!m_assetsManager.load_font("mainFont", "Assets/Tuffy.ttf")
			or !m_assetsManager.load_texture("boardTexture", "Assets/board.png")
			or !m_assetsManager.load_texture("circleTexture", "Assets/circle.png")
			or !m_assetsManager.load_texture("crossTexture", "Assets/cross.png")) {
			throw std::runtime_error("Failed to load assets");
		}
	}

	void Renderer::run() {
		BoardView boardView(m_gameState, m_assetsManager);

		while (m_window.isOpen()) {
			processEvents();
			update();
			render(boardView);
		}
	}

	void Renderer::processEvents() {
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
				if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
					if (mouse->button == sf::Mouse::Button::Left) {
						const sf::Vector2i mousePos = { mouse->position.x, mouse->position.y };
						const sf::Vector2i gridPos = { mousePos.x / 200, mousePos.y / 200 };

						m_gameState.make_move(gridPos.x, gridPos.y);
					}
				}
			}

			if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>()) {
				m_mousePosition = { mouseMove->position.x, mouseMove->position.y };
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

		_boardView.draw(m_window, m_mousePosition);

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
	}

}