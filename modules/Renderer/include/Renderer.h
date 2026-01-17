#pragma once
#include <GameState.h>
#include "BoardView.h"
#include "AssetsManager.h"
#include "TextRenderer.h"
#include <AppState.h>
#include "IScreen.h"
#include <SFML/Graphics.hpp>

namespace Renderer {
	class Renderer {
	public:

		Renderer(EngineCore::GameState& _gameState);

		void run();

		void switch_state(AppState _newState);

	private:
		EngineCore::GameState& m_gameState;
		AppState m_appState;

		sf::RenderWindow m_window;
		std::unique_ptr<IScreen> m_currentScreen;
		TextRenderer m_textRenderer;

		AssetsManager m_assetsManager;
	};
}