#pragma once
#include <SFML/Graphics.hpp>

namespace EngineCore { class GameState; }

namespace Renderer {
	class Renderer {
	public:

		Renderer(EngineCore::GameState& _gameState);

		void run();

	private:

		void processEvents();
		void update();
		void render();

	private:
		EngineCore::GameState& m_gameState;
		sf::RenderWindow m_window;
	};
}