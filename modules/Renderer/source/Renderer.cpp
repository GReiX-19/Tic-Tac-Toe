#include "Renderer.h"
#include <SFML/Window/Event.hpp>

namespace Renderer {

	Renderer::Renderer(EngineCore::GameState& _gameState)
		: m_gameState(_gameState)
		, m_window(sf::VideoMode({ 600, 600 }), "Tic Tac Toe") {
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

			if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouse->button == sf::Mouse::Button::Left) {
					const sf::Vector2i mousePos = { mouse->position.x, mouse->position.y };
					const sf::Vector2i gridPos = { mousePos.x / 200, mousePos.y / 200 };
					
					m_gameState.make_move(gridPos.x, gridPos.y);
				}
			}
		}
	}

	void Renderer::update() {
		// Update game state if necessary
	}

	void Renderer::render(BoardView& _boardView) {
		m_window.clear(sf::Color::Black);

		_boardView.draw(m_window);

		m_window.display();
	}

}