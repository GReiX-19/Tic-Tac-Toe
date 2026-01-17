#pragma once
#include <GameState.h>
#include "BoardView.h"
#include "RenderState.h"
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

	private:

		void processEvents();
		void update();
		void render(BoardView& _boardView);

		void switch_state(AppState& _newState);

	private:
		EngineCore::GameState& m_gameState;
		sf::RenderWindow m_window;

		AppState m_appState;
		std::unique_ptr<IScreen> m_currentScreen;

		RenderState m_renderState;
		EngineCore::Player m_winner;

		AssetsManager m_assetsManager;
		TextRenderer m_textRenderer;

		sf::Vector2i m_mousePosition;
		sf::Vector2i m_keyboardCursorPos;
		bool m_isUsingKeyboard = false;
	};
}