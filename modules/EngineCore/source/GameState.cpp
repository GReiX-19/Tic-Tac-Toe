#include "GameState.h"

namespace EngineCore {
	GameState::GameState()
		: m_board(), m_current_player(Player::PLAYER_X) {
	}

	bool GameState::make_move(int _row, int _col, Player _player) {
		CellState state = (_player == Player::PLAYER_X) ? CellState::X : CellState::O;
		if (m_board.set_cell(_row, _col, state)) {
			m_current_player = (_player == Player::PLAYER_X) ? Player::PLAYER_O : Player::PLAYER_X;
			return true;
		}
		return false;
	}

	bool GameState::is_win(Player _player) const {
		CellState state = (_player == Player::PLAYER_X) ? CellState::X : CellState::O;
		return check_win_for(state);
	}

	bool GameState::check_win_for(CellState _state) const {
		// Check rows and columns
		for (int i = 0; i < 3; ++i) {
			if ((m_board.get_cell(i, 0) == _state && m_board.get_cell(i, 1) == _state && m_board.get_cell(i, 2) == _state) ||
				(m_board.get_cell(0, i) == _state && m_board.get_cell(1, i) == _state && m_board.get_cell(2, i) == _state)) {
				return true;
			}
		}
		// Check diagonals
		if ((m_board.get_cell(0, 0) == _state && m_board.get_cell(1, 1) == _state && m_board.get_cell(2, 2) == _state) ||
			(m_board.get_cell(0, 2) == _state && m_board.get_cell(1, 1) == _state && m_board.get_cell(2, 0) == _state)) {
			return true;
		}
		return false;
	}

	bool GameState::is_draw() const {
		return m_board.is_full() && !is_win(Player::PLAYER_X) && !is_win(Player::PLAYER_O);
	}

	void GameState::reset() {
		m_board.reset();
		m_current_player = Player::PLAYER_X;
	}

	Player GameState::get_current_player() const {
		return m_current_player;
	}
	const Board& GameState::get_board() const {
		return m_board;
	}
}