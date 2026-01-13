#include "Renderer.h"
#include "BoardView.h"
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
			render();
		}
	}

	void Renderer::processEvents() {
		while (const std::optional event = m_window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				m_window.close();
			}
		}
	}

	void Renderer::update() {
		// Update game state if necessary
	}

	void Renderer::render() {
		
	}

}