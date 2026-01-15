#include "BoardView.h"
#include "GameState.h"
#include "Board.h"
#include "CellState.h"

namespace Renderer {
		
	BoardView::BoardView(const EngineCore::GameState& _gameState, AssetsManager& _assetsManager)
		: m_gameState(_gameState), m_cellSize(600.f / 3.f), m_assetsManager(_assetsManager) {
	}

	void BoardView::draw(sf::RenderWindow& _window) {
		sf::Sprite boardSprite(m_assetsManager.get_texture("boardTexture"));
		_window.draw(boardSprite);

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

}