#pragma once
#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

namespace EngineCore { class GameState; }

namespace Renderer {
	class BoardView {
	public:

		BoardView(const EngineCore::GameState& _gameState, AssetsManager& _assetsManager);

		void draw_board(sf::RenderWindow& _window);
		void draw_marks(sf::RenderWindow& _window);
		void draw_win_line(sf::RenderWindow& _window);
		void highlight_cell(sf::RenderWindow& _window, sf::Vector2i& _mousePosition);

		void draw(sf::RenderWindow& _window, sf::Vector2i& _mousePosition);

	private:
		const EngineCore::GameState& m_gameState;
		AssetsManager& m_assetsManager;
		float m_cellSize;
	};
}