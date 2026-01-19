#include "CellState.h"
#include "Board.h"

namespace EngineCore {
	Board::Board() {
		reset();
	}
	CellState Board::get_CellState(uint16_t _row, uint16_t _col) const {
		return m_cells[_row][_col];
	}
	bool Board::set_CellState(uint16_t _row, uint16_t _col, CellState _state) {
		if (m_cells[_row][_col] == CellState::EMPTY) {
			m_cells[_row][_col] = _state;
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