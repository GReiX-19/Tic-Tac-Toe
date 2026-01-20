#pragma once
#include "IScreen.h"
#include "TextRenderer.h"
#include "BoardView.h"
#include "AssetsManager.h"

namespace Renderer {
	class Renderer;

	class GameScreen : public IScreen {
	public:

		GameScreen(Renderer& _renderer, AssetsManager& _assetsManager, EngineCore::GameState& state);

		void handle_event(const sf::Event& _event) override;
		void update(float _dt) override;
		void draw(sf::RenderWindow& _window) override;

	private:
		Renderer& m_renderer;
		AssetsManager& m_assetsManager;
		EngineCore::GameState& m_gameState;
		TextRenderer m_textRenderer;

		BoardView m_boardView;

		sf::Vector2i m_mousePosition;
		sf::Vector2i m_keyboardCursorPos;
		bool m_isUsingKeyboard = false;
	};
}