#pragma once
#include <SFML/Graphics.hpp>
#include "AssetsManager.h"

namespace EngineCore { class GameState; }

namespace Renderer {
	class BoardView {
	public:

		BoardView(const EngineCore::GameState& _gameState, AssetsManager& _assetsManager);

		void draw(sf::RenderWindow& _window);

	private:
		const EngineCore::GameState& m_gameState;
		AssetsManager& m_assetsManager;
		float m_cellSize;
	};
}