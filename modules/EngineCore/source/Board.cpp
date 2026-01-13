#include "Board.h"

namespace EngineCore {
	Board::Board() {
		reset();
	}
	CellState Board::get_CellState(int row, int col) const {
		return m_cells[row][col];
	}
	bool Board::set_CellState(int row, int col, CellState state) {
		if (m_cells[row][col] == CellState::Empty) {
			m_cells[row][col] = state;
			return true;
		}
		return false;
	}
	void Board::reset() {
		for (auto& row : m_cells) {
			row.fill(CellState::Empty);
		}
	}
}