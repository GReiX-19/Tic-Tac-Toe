#pragma once
#include <AppState.h>
#include "AssetsManager.h"
#include "RenderScreens/IScreen.h"
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

namespace EngineCore {
	class GameState;
}

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

		AssetsManager m_assetsManager;
	};
}