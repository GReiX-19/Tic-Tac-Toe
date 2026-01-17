#pragma once
#include "IScreen.h"
#include "AssetsManager.h"
#include "Renderer.h"

namespace Renderer {
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

		BoardView m_boardView;

		sf::Vector2i m_mousePosition;
		sf::Vector2i m_keyboardCursorPos;
		bool m_isUsingKeyboard = false;

		EngineCore::Player m_winner = EngineCore::Player::PLAYER_X;
	};
}