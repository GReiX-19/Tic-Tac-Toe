#include "GameState.h"
#include "CellState.h"

namespace EngineCore {
	GameState::GameState()
		: m_board(), m_current_player(Player::PLAYER_X), m_winner(Player::PLAYER_X) {
	}

	bool GameState::make_move(uint16_t _row, uint16_t _col) {
		CellState state = (m_current_player == Player::PLAYER_X) ? CellState::X : CellState::O;
		if (m_board.set_CellState(_row, _col, state)) {
			m_current_player = (m_current_player == Player::PLAYER_X) ? Player::PLAYER_O : Player::PLAYER_X;
			return true;
		}
		return false;
	}
	bool GameState::is_win(Player _player) const {
		CellState state = (_player == Player::PLAYER_X) ? CellState::X : CellState::O;
		return check_win_for(state);
	}
	bool GameState::is_draw() const {
		return m_board.is_full() && !is_win(Player::PLAYER_X) && !is_win(Player::PLAYER_O);
	}

	const Board& GameState::get_board() const {
		return m_board;
	}
	GameState::winInfo GameState::get_win_info() const {
		winInfo info;
		// Check rows
		for (int i = 0; i < 3; ++i) {
			if (m_board.get_CellState(i, 0) != CellState::EMPTY &&
				m_board.get_CellState(i, 0) == m_board.get_CellState(i, 1) &&
				m_board.get_CellState(i, 1) == m_board.get_CellState(i, 2)) {
				info.isWin = true;
				info.row = -1;
				info.col = i;
				info.isDiagonal = false;
				return info;
			}
		}
		// Check columns
		for (int i = 0; i < 3; ++i) {
			if (m_board.get_CellState(0, i) != CellState::EMPTY &&
				m_board.get_CellState(0, i) == m_board.get_CellState(1, i) &&
				m_board.get_CellState(1, i) == m_board.get_CellState(2, i)) {
				info.isWin = true;
				info.row = i;
				info.col = -1;
				info.isDiagonal = false;
				return info;
			}
		}
		// Check diagonals
		if (m_board.get_CellState(0, 0) != CellState::EMPTY &&
			m_board.get_CellState(0, 0) == m_board.get_CellState(1, 1) &&
			m_board.get_CellState(1, 1) == m_board.get_CellState(2, 2)) {
			info.isWin = true;
			info.row = -1;
			info.col = -1;
			info.isDiagonal = true;
			info.isAntiDiagonal = false;
			return info;
		}
		if (m_board.get_CellState(0, 2) != CellState::EMPTY &&
			m_board.get_CellState(0, 2) == m_board.get_CellState(1, 1) &&
			m_board.get_CellState(1, 1) == m_board.get_CellState(2, 0)) {
			info.isWin = true;
			info.row = -1;
			info.col = -1;
			info.isDiagonal = false;
			info.isAntiDiagonal = true;
			return info;
		}
		return info;
	}

	void GameState::reset() {
		m_board.reset();
		m_current_player = Player::PLAYER_X;
	}

	bool GameState::check_win_for(CellState _state) const {
		// Check rows and columns
		for (int i = 0; i < 3; ++i) {
			if ((m_board.get_CellState(i, 0) == _state && m_board.get_CellState(i, 1) == _state && m_board.get_CellState(i, 2) == _state) ||
				(m_board.get_CellState(0, i) == _state && m_board.get_CellState(1, i) == _state && m_board.get_CellState(2, i) == _state)) {
				return true;
			}
		}
		// Check diagonals
		if ((m_board.get_CellState(0, 0) == _state && m_board.get_CellState(1, 1) == _state && m_board.get_CellState(2, 2) == _state) ||
			(m_board.get_CellState(0, 2) == _state && m_board.get_CellState(1, 1) == _state && m_board.get_CellState(2, 0) == _state)) {
			return true;
		}
		return false;
	}
}