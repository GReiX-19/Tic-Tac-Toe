#pragma once
#include <GameState.h>
#include "BoardView.h"
#include "RenderState.h"
#include <SFML/Graphics.hpp>

namespace Renderer {
	class Renderer {
	public:

		Renderer(EngineCore::GameState& _gameState);

		void run();

	private:

		void processEvents();
		void update();
		void render(BoardView& _boardView);

	private:
		EngineCore::GameState& m_gameState;
		sf::RenderWindow m_window;

		RenderState m_renderState;
		EngineCore::Player m_winner;
	};
}