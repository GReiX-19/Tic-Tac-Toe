#include "GameApp.h"

namespace GameApp {

	GameApp::GameApp() : m_gameState(), m_assetsManager(), m_renderer(m_gameState, m_assetsManager) {}

	void GameApp::execute() {
		m_renderer.run();
	}

}