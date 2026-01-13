#include "BoardView.h"
#include "GameState.h"
#include "Board.h"
#include "CellState.h"

namespace Renderer {
		
	BoardView::BoardView(const EngineCore::GameState& _gameState)
		: m_gameState(_gameState), m_cellSize(600.f / 3.f) {
	}

	void BoardView::draw(sf::RenderWindow& _window) {
		draw_grid(_window);
		draw_pieces(_window);
	}

	void BoardView::draw_grid(sf::RenderWindow& _window) {
		sf::RectangleShape line;
		line.setFillColor(sf::Color::Yellow);
		// Vertical lines
		for (int i = 1; i <= 3; i++) {
			line.setSize(sf::Vector2f(5.f, 600.f));
			line.setPosition({ i * m_cellSize, 0.f });
			_window.draw(line);
		}
		// Horizontal lines
		for (int i = 1; i <= 3; ++i) {
			line.setSize(sf::Vector2f(600.f, 5.f));
			line.setPosition({ 0.f, i * m_cellSize});
			_window.draw(line);
		}
	}

	void BoardView::draw_pieces(sf::RenderWindow& _window) {
		const auto& board = m_gameState.get_board();

		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				auto cell = board.get_CellState(row, col);

				float x = row * m_cellSize;
				float y = col * m_cellSize;

				if (cell == EngineCore::CellState::X) {
					sf::RectangleShape line1({ m_cellSize - 40.f, 10.f });
					sf::RectangleShape line2({ m_cellSize - 40.f, 10.f });

					line1.setFillColor(sf::Color::Red);
					line2.setFillColor(sf::Color::Red);

					line1.setOrigin({ line1.getSize().x / 2.f, line1.getSize().y / 2.f });
					line2.setOrigin({ line1.getSize().x / 2.f, line1.getSize().y / 2.f });

					line1.setPosition({ x + m_cellSize / 2.f, y + m_cellSize / 2.f });
					line1.setRotation(sf::degrees(45));

					line2.setPosition({ x + m_cellSize / 2.f, y + m_cellSize / 2.f });
					line2.setRotation(sf::degrees(-45));

					_window.draw(line1);
					_window.draw(line2);
				}
				else if (cell == EngineCore::CellState::O) {
					sf::CircleShape circle(m_cellSize / 2.5f);
					circle.setFillColor(sf::Color::Transparent);
					circle.setOutlineColor(sf::Color::Blue);
					circle.setOutlineThickness(10.f);

					circle.setOrigin({ circle.getRadius(), circle.getRadius()});
					circle.setPosition({ x + m_cellSize / 2.f, y + m_cellSize / 2.f });
					_window.draw(circle);
				}
			}
		}
	}

}