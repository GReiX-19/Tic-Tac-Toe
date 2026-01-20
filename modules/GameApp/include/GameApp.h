#pragma once
#include "GameState.h"
#include "Renderer.h"

namespace GameApp {
	class GameApp {
	public:

		GameApp();

		void execute();

	private:
		EngineCore::GameState m_gameState;
		Renderer::Renderer m_renderer;
	};
}