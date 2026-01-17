#pragma once
#include "IScreen.h"
#include "AssetsManager.h"
#include "Renderer.h"

namespace Renderer {
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

		sf::Text m_gameOverText;
		sf::Text m_restartInstructionText;
	};
}