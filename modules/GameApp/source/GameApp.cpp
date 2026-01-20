#include "GameApp.h"

namespace GameApp {
	GameApp::GameApp() : m_gameState(), m_renderer(m_gameState) {}

	void GameApp::execute() {
		m_renderer.run();
	}
}