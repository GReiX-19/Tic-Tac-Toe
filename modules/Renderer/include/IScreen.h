#pragma once
#include <SFML/Graphics.hpp>

namespace Renderer {
	class IScreen {
	public:

		virtual ~IScreen() = default;

		virtual void handle_event(const sf::Event& _event) = 0;
		virtual void update(float _dt) = 0;
		virtual void draw(sf::RenderWindow& _window) = 0;
	};
}