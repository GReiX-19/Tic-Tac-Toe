#pragma once
#include "GameState.h"
#include "AssetsManager.h"
#include "Renderer.h"

namespace GameApp {

	class GameApp {
	public:

		GameApp();

		void execute();

	private:
		EngineCore::GameState m_gameState;
		AssetsManager m_assetsManager;
		Renderer::Renderer m_renderer;
	};

}