#include "Renderer.h"
#include "RenderScreens/MenuScreen.h"
#include "RenderScreens/GameScreen.h"
#include "RenderScreens/GameOverScreen.h"
#include <SFML/Window/Event.hpp>

namespace Renderer {

	Renderer::Renderer(EngineCore::GameState& _gameState)
		: m_gameState(_gameState)
		, m_appState(AppState::Menu)
		, m_window(sf::VideoMode({ 600, 600 }), "Tic Tac Toe", sf::Style::Titlebar | sf::Style::Close)
		, m_assetsManager() {
		m_window.setFramerateLimit(60);

		if (!m_assetsManager.load_font("mainFont", "Assets/AveriaGruesaLibre-Regular.ttf")
			or !m_assetsManager.load_texture("boardTexture", "Assets/board.png")
			or !m_assetsManager.load_texture("circleTexture", "Assets/circle.png")
			or !m_assetsManager.load_texture("crossTexture", "Assets/cross.png")) {
			throw std::runtime_error("Failed to load assets");
		}
	}

	void Renderer::run() {
		switch_state(AppState::Menu);

		sf::Clock clock;

		while (m_window.isOpen()) {
			while (const std::optional event = m_window.pollEvent()) {

				if (event->is<sf::Event::Closed>()) {
					m_window.close();
				}
				else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
					if (key->scancode == sf::Keyboard::Scan::Escape) {
						m_window.close();
					}
				}
				m_currentScreen->handle_event(event.value());

			}

			const float dt = clock.restart().asSeconds();
			m_currentScreen->update(dt);

			m_window.clear(sf::Color::Black);
			m_currentScreen->draw(m_window);
			m_window.display();
		}
	}

	void Renderer::switch_state(AppState _newState) {
		m_appState = _newState;

		switch (_newState) {
		case AppState::Menu:
			m_currentScreen = std::make_unique<MenuScreen>(*this, m_assetsManager);
			break;
		case AppState::Game:
			m_currentScreen = std::make_unique<GameScreen>(*this, m_assetsManager, m_gameState);
			break;
		case AppState::GameOver:
			m_currentScreen = std::make_unique<GameOverScreen>(*this, m_assetsManager, m_gameState);
			break;
		}
	}

}