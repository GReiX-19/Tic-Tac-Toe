#include "Bot.h"
#include "CellState.h"
#include "Board.h"

namespace EngineCore {
	Bot::Bot(PlayerMark _playerStatus) : IPlayer(_playerStatus) {}

	void Bot::make_move(Board& _board) {
		CellState state = (get_status() == PlayerMark::PLAYER_X) ? CellState::X : CellState::O;
		std::pair<uint16_t, uint16_t> cell;

		if (can_win(_board, cell, state))
			_board.set_CellState(cell, state);
		if (can_win(_board, cell, state))
			_board.set_CellState(cell, state);
		if (can_win(_board, cell, state))
			_board.set_CellState(cell, state);
		
		find_any(_board, cell);
		_board.set_CellState(cell, state);
	}

	PlayerMark Bot::get_status() const {
		return m_playerStatus;
	}

	bool Bot::can_win(const Board& _board, std::pair<uint16_t, uint16_t>& _cell, CellState _state) {
		for (uint16_t row = 0; row < 3; row++) {
			for (uint16_t col = 0; col < 3; col++) {
				if (_board.get_CellState({ row, col }) != CellState::EMPTY)
					continue;

				Board copiedBoard = _board;
				copiedBoard.set_CellState({ row, col }, _state);
				if (check_win(copiedBoard, _state)) {
					_cell.first = row;
					_cell.second = col;
					return true;
				}
			}
		}

		return false;
	}
	bool Bot::find_center(const Board& _board, std::pair<uint16_t, uint16_t>& _cell) {
		if (_board.get_CellState({ 1,1 }) == CellState::EMPTY) {
			_cell.first = 1;
			_cell.second = 1;
			return true;
		}

		return false;
	}
	bool Bot::find_corner(const Board& _board, std::pair<uint16_t, uint16_t>& _cell) {
		const std::pair<uint16_t, uint16_t> corners[4] = {
			{0,0},
			{0,2},
			{2,0},
			{2,2}
		};

		for (auto cell : corners) {
			if (_board.get_CellState(cell) == CellState::EMPTY) {
				_cell.first = cell.first;
				_cell.second = cell.second;
				return true;
			}
		}

		return false;
	}
	bool Bot::find_any(const Board& _board, std::pair<uint16_t, uint16_t>& _cell) {
		for (uint16_t row = 0; row < 3; row++) {
			for (uint16_t col = 0; col < 3; col++) {
				if (_board.get_CellState({row, col}) == CellState::EMPTY) {
					_cell.first = row;
					_cell.second = col;
					return true;
				}
			}
		}

		return false;
	}

	bool Bot::check_win(const Board& _board, CellState _state) {
		for (int i = 0; i < 3; ++i) {
			if ((_board.get_CellState({ i, 0 }) == _state && _board.get_CellState({ i, 1 }) == _state && _board.get_CellState({ i, 2 }) == _state) ||
				(_board.get_CellState({ 0, i }) == _state && _board.get_CellState({ 1, i }) == _state && _board.get_CellState({ 2, i }) == _state)) {
				return true;
			}
		}
		// Check diagonals
		if ((_board.get_CellState({ 0, 0 }) == _state && _board.get_CellState({ 1, 1 }) == _state && _board.get_CellState({ 2, 2 }) == _state) ||
			(_board.get_CellState({ 0, 2 }) == _state && _board.get_CellState({ 1, 1 }) == _state && _board.get_CellState({ 2, 0 }) == _state)) {
			return true;
		}
		return false;
	}
}