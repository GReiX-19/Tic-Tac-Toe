#include "CellState.h"
#include "Board.h"

namespace EngineCore {
	Board::Board() {
		reset();
	}
	CellState Board::get_CellState(std::pair<uint16_t, uint16_t> _cell) const {
		return m_cells[_cell.first][_cell.second];
	}
	bool Board::set_CellState(std::pair<uint16_t, uint16_t> _cell, CellState _state) {
		if (m_cells[_cell.first][_cell.second] == CellState::EMPTY) {
			m_cells[_cell.first][_cell.second] = _state;
			return true;
		}
		return false;
	}

	bool Board::is_full() const {
		for (const auto& row : m_cells) {
			for (const auto& cell : row) {
				if (cell == CellState::EMPTY) {
					return false;
				}
			}
		}
		return true;
	}

	void Board::reset() {
		for (auto& row : m_cells) {
			row.fill(CellState::EMPTY);
		}
	}
}