#pragma once
#include "IScreen.h"
#include "TextRenderer.h"
#include "BoardView.h"
#include <SFML/Graphics.hpp>

namespace EngineCore {
	class GameState;
}

class AssetsManager;

namespace Renderer {
	class Renderer;

	class GameOverScreen : public IScreen {
	public:

		GameOverScreen(Renderer& _renderer, AssetsManager& _assetsManager, EngineCore::GameState& state);
		void handle_event(const sf::Event& _event) override;
		void update(float _dt) override;
		void draw(sf::RenderWindow& _window) override;

	private:
		Renderer& m_renderer;
		AssetsManager& m_assetsManager;
		EngineCore::GameState& m_gameState;
		TextRenderer m_textRenderer;

		BoardView m_boardView;

		sf::Sprite m_restartButton;
		sf::Sprite m_menuButton;
	};
}