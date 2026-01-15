#include "BoardView.h"
#include "GameState.h"
#include "Board.h"
#include "CellState.h"

namespace Renderer {
		
	BoardView::BoardView(const EngineCore::GameState& _gameState, AssetsManager& _assetsManager)
		: m_gameState(_gameState), m_cellSize(600.f / 3.f), m_assetsManager(_assetsManager) {
	}

	void BoardView::draw_board(sf::RenderWindow& _window) {
		sf::Sprite boardSprite(m_assetsManager.get_texture("boardTexture"));
		_window.draw(boardSprite);
	}

	void BoardView::draw_marks(sf::RenderWindow& _window) {
		const auto& board = m_gameState.get_board();

		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				auto cell = board.get_CellState(row, col);

				if (cell != EngineCore::CellState::EMPTY) {
					sf::Sprite cellSprite(cell == EngineCore::CellState::X ?
						m_assetsManager.get_texture("crossTexture") :
						m_assetsManager.get_texture("circleTexture"));
					cellSprite.setPosition({ row * m_cellSize, col * m_cellSize });
					_window.draw(cellSprite);
				}

			}
		}
	}

	void BoardView::draw_win_line(sf::RenderWindow& _window) {
		auto info = m_gameState.get_win_info();
		if (!info.isWin) {
			return;
		}

		sf::RectangleShape line;
		line.setFillColor(sf::Color::Red);
		line.setSize({ 1000.f, 10.f });
		line.setOrigin({ 0.f, 5.f });

		if (info.row != -1) {
			line.setPosition({ 0.f, info.row * m_cellSize + m_cellSize / 2.f });
		}
		else if (info.col != -1) {
			line.setRotation(sf::degrees(90.f));
			line.setPosition({ info.col * m_cellSize + m_cellSize / 2.f, 0.f });
		}
		else if (info.isDiagonal) {
			line.setPosition({ 0.f, 0.f });
			line.setRotation(sf::degrees(45.f));
		}
		else if (info.isAntiDiagonal) {
			line.setPosition({ 600.f, 0.f });
			line.setRotation(sf::degrees(135.f));
		}

		_window.draw(line);
	}

	void BoardView::mouseHighlight_cell(sf::RenderWindow& _window, sf::Vector2i& _mousePosition) {
		if (_mousePosition.x < 0 or _mousePosition.x >= 600
			or _mousePosition.y < 0 or _mousePosition.y >= 600) {
			return;
		}

		int col = _mousePosition.x / static_cast<int>(m_cellSize);
		int row = _mousePosition.y / static_cast<int>(m_cellSize);

		sf::RectangleShape highlightRect({ m_cellSize, m_cellSize });
		highlightRect.setPosition({ col * m_cellSize, row * m_cellSize });
		if (m_gameState.get_board().get_CellState(col, row) != EngineCore::CellState::EMPTY) 
			highlightRect.setFillColor(sf::Color(255, 0, 0, 50));
		else
			highlightRect.setFillColor(sf::Color(255, 255, 0, 100));

		_window.draw(highlightRect);
	}

	void BoardView::keyboardHighlight_cell(sf::RenderWindow& _window, sf::Vector2i& _keyboardCursorPos) {
		sf::RectangleShape highlightRect({ m_cellSize, m_cellSize });
		highlightRect.setPosition({ _keyboardCursorPos.x * m_cellSize, _keyboardCursorPos.y * m_cellSize });
		if (m_gameState.get_board().get_CellState(_keyboardCursorPos.x, _keyboardCursorPos.y) != EngineCore::CellState::EMPTY)
			highlightRect.setFillColor(sf::Color(255, 0, 0, 50));
		else
			highlightRect.setFillColor(sf::Color(255, 255, 0, 100));

		_window.draw(highlightRect);
	}

	void BoardView::draw(sf::RenderWindow& _window, sf::Vector2i& _mousePosition, sf::Vector2i& _keyboardCursorPos, bool& _isUsingKeyboard) {
		draw_board(_window);
		draw_marks(_window);
		if (_isUsingKeyboard)
			keyboardHighlight_cell(_window, _keyboardCursorPos);
		else 
			mouseHighlight_cell(_window, _mousePosition);
		draw_win_line(_window);
	}
}