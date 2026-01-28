#include "Bot.h"

namespace EngineCore {
	Bot::Bot(CellState _botState) : m_botState(_botState) {
		m_playerState = _botState == CellState::X ? CellState::O : CellState::X;
	}

	std::pair<uint16_t, uint16_t> Bot::get_move(const Board& _board) {
		uint16_t row, col;

		if (can_win(_board, row, col, m_botState))
			return { std::move(row), std::move(col) };

		if (can_win(_board, row, col, m_playerState))
			return { std::move(row), std::move(col) };

		if (find_center(_board, row, col))
			return { std::move(row), std::move(col) };

		if (find_corner(_board, row, col))
			return { std::move(row), std::move(col) };

		if (find_any(_board, row, col))
			return { std::move(row), std::move(col) };
	}

	bool Bot::can_win(const Board& _board, uint16_t& _outRow, uint16_t _outCol, CellState _state) {
		for (size_t row = 0; row < 3; row++) {
			for (size_t col = 0; col < 3; col++) {
				if (_board.get_CellState(row, col) != CellState::EMPTY)
					continue;

				Board copied = _board;
				copied.set_CellState(row, col, _state);

				if (check_win(copied, _state)) {
					_outRow = row;
					_outCol = col;
					return true;
				}
			}
		}
		return false;
	}
	bool Bot::find_center(const Board& _board, uint16_t& _outRow, uint16_t _outCol) {
		if (_board.get_CellState(1, 1) == CellState::EMPTY) {
			_outRow = 1;
			_outCol = 1;
			return true;
		}
		return false;
	}
	bool Bot::find_corner(const Board& _board, uint16_t& _outRow, uint16_t _outCol) {
		const std::pair<uint16_t, uint16_t> corners[4] = {
			{0, 0},
			{0 ,2},
			{2 ,0},
			{2 ,2}
		};

		for (auto [row, col] : corners) {
			if (_board.get_CellState(row, col) == CellState::EMPTY) {
				_outRow = row;
				_outCol = col;
				return true;
			}
		}
		return false;
	}
	bool Bot::find_any(const Board& _board, uint16_t& _outRow, uint16_t _outCol) {
		for (size_t row = 0; row < 3; row++) {
			for (size_t col = 0; col < 3; col++) {
				if (_board.get_CellState(row, col) == CellState::EMPTY) {
					_outRow = row;
					_outCol = col;
					return true;
				}
			}
		}
		return false;
	}

	bool Bot::check_win(const Board& _board, CellState _state) {
		//строки
		for (size_t row = 0; row < 3; row++) {
			if (_board.get_CellState(row, 0) == _state
				and _board.get_CellState(row, 1) == _state
				and _board.get_CellState(row, 2) == _state)
				return true;
		}
		//столбцы
		for (size_t col = 0; col < 3; col++) {
			if (_board.get_CellState(0, col) == _state
				and _board.get_CellState(1, col) == _state
				and _board.get_CellState(2, col) == _state)
				return true;
		}
		//главная диагональ
		if (_board.get_CellState(0, 0) == _state
			and _board.get_CellState(1, 1) == _state
			and _board.get_CellState(2, 2) == _state)
			return true;
		//побочная диагональ
		if (_board.get_CellState(0, 2) == _state
			and _board.get_CellState(1, 1) == _state
			and _board.get_CellState(2, 0) == _state)
			return true;

		return false;
	}
}