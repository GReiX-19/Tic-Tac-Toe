#include "Renderer.h"
#include "AssetsManager.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include "RenderScreens/MenuScreen.h"
#include "RenderScreens/GameScreen.h"
#include "RenderScreens/GameOverScreen.h"

namespace Renderer {

	Renderer::Renderer(EngineCore::GameState& _gameState, AssetsManager& _assetsManager)
		: m_gameState(_gameState)
		, m_appState(AppState::Menu)
		, m_window(sf::VideoMode({ 600, 700 }), "Tic Tac Toe", sf::Style::Titlebar | sf::Style::Close)
		, m_assetsManager(_assetsManager) {
		m_window.setFramerateLimit(60);
		m_window.setIcon(m_assetsManager.get_texture("gameIcon").copyToImage());
	}

	void Renderer::run() {
		switch_state(AppState::Menu);

		sf::Clock clock;

		while (m_window.isOpen()) {
			while (const std::optional event = m_window.pollEvent()) {

				if (event->is<sf::Event::Closed>()) {
					m_window.close();
				}

				m_currentScreen->handle_event(event.value());

			}

			const float dt = clock.restart().asSeconds();
			m_currentScreen->update(dt);

			m_window.clear(sf::Color(96, 111, 206));
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
		case AppState::Exit:
			m_window.close();
			break;
		}
	}

}