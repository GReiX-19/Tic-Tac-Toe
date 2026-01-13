#include "Renderer.h"
#include <SFML/Window/Event.hpp>

namespace Renderer {

	Renderer::Renderer(EngineCore::GameState& _gameState)
		: m_gameState(_gameState)
		, m_window(sf::VideoMode({ 600, 600 }), "Tic Tac Toe")
		, m_renderState(RenderState::Playing)
		, m_winner() {
		m_window.setFramerateLimit(60);
	}

	void Renderer::run() {
		BoardView boardView(m_gameState);

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

		sf::Font font("Assets/Tuffy.ttf");
		sf::Text text(font);

		text.setCharacterSize(70);
		text.setFillColor(sf::Color::White);
		text.setPosition({100, 250});

		_boardView.draw(m_window);

		if (m_renderState == RenderState::GameOver) {
			if (m_winner == EngineCore::Player::PLAYER_X) {
				text.setString("Player X Wins!");
			}
			else if (m_winner == EngineCore::Player::PLAYER_O) {
				text.setString("Player O Wins!");
			}
			else {
				text.setString("It's a Draw!");
			}
			m_window.draw(text);
		}

		m_window.display();
	}

}