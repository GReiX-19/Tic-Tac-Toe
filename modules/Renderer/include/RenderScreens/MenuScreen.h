#pragma once
#include "IScreen.h"
#include "TextRenderer.h"
#include <SFML/Graphics/Sprite.hpp>

namespace sf {
	class Event;
	class RenderWindow;
}

namespace Renderer {
	class Renderer;
	class AssetsManager;

	class MenuScreen : public IScreen {
	public:

		MenuScreen(Renderer& _renderer, AssetsManager& _assetsManager);

		void handle_event(const sf::Event& _event) override;
		void update(float _dt) override;
		void draw(sf::RenderWindow& _window) override;

	private:
		Renderer& m_renderer;
		AssetsManager& m_assetsManager;
		TextRenderer m_textRenderer;

		sf::Sprite m_playButton;
		sf::Sprite m_exitButton;
	};
}