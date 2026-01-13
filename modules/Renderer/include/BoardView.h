#pragma once
#include <SFML/Graphics.hpp>

namespace EngineCore { class GameState; }

namespace Renderer {
	class BoardView {
	public:

		BoardView(const EngineCore::GameState& _gameState);

		void draw(sf::RenderWindow& _window);

	private:
		void draw_grid(sf::RenderWindow& _window);
		void draw_pieces(sf::RenderWindow& _window);

	private:
		const EngineCore::GameState& m_gameState;
		float m_cellSize;
	}
}