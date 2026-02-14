#pragma once
#include "IScreen.h"
#include "TextRenderer.h"
#include <SFML/Graphics/Sprite.hpp>

namespace EngineCore {
	class GameState;
}

class AssetsManager;

namespace Renderer {
	class Renderer;

	class GameModeScreen : public IScreen {
	public:

		GameModeScreen(Renderer& _renderer, AssetsManager& _assetsManager, EngineCore::GameState& _gameState);

		void handle_event(const sf::Event& _event) override;
		void update(float _dt) override;
		void draw(sf::RenderWindow& _window) override;

	private:
		Renderer& m_renderer;
		AssetsManager& m_assetsManager;
		EngineCore::GameState& m_gameState;
		TextRenderer m_textRenderer;

		sf::Sprite m_vsBotButton;
	};
}