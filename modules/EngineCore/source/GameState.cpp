#include "GameState.h"
#include "CellState.h"

namespace EngineCore {
	GameState::GameState()
		: m_board(), m_user(PlayerMark::PLAYER_X), m_bot(PlayerMark::PLAYER_O), m_vsBot(true), m_crossWins(0), m_cicleWins(0) {
	}

	bool GameState::make_move(const std::pair<uint16_t, uint16_t>& _cell) {
		m_user.make_move(m_board, _cell);
		m_bot.make_move(m_board);
	}
	bool GameState::is_win(PlayerMark _player) {
		CellState state = (_player == PlayerMark::PLAYER_X) ? CellState::X : CellState::O;
		return check_win_for(state);
	}
	bool GameState::is_draw() {
		return m_board.is_full() && !is_win(m_user.get_status()) && !is_win(m_bot.get_status());
	}

	const Board& GameState::get_board() const {
		return m_board;
	}
	GameState::winInfo GameState::get_win_info() const {
		winInfo info;
		// Check rows
		for (int i = 0; i < 3; ++i) {
			if (m_board.get_CellState({ i, 0 }) != CellState::EMPTY &&
				m_board.get_CellState({ i, 0 }) == m_board.get_CellState({ i, 1 }) &&
				m_board.get_CellState({ i, 1 }) == m_board.get_CellState({ i, 2 })) {
				info.isWin = true;
				info.row = -1;
				info.col = i;
				info.isDiagonal = false;
				return info;
			}
		}
		// Check columns
		for (int i = 0; i < 3; ++i) {
			if (m_board.get_CellState({ 0, i }) != CellState::EMPTY &&
				m_board.get_CellState({ 0, i }) == m_board.get_CellState({ 1, i }) &&
				m_board.get_CellState({ 1, i }) == m_board.get_CellState({ 2, i })) {
				info.isWin = true;
				info.row = i;
				info.col = -1;
				info.isDiagonal = false;
				return info;
			}
		}
		// Check diagonals
		if (m_board.get_CellState({ 0, 0 }) != CellState::EMPTY &&
			m_board.get_CellState({ 0, 0 }) == m_board.get_CellState({ 1, 1 }) &&
			m_board.get_CellState({ 1, 1 }) == m_board.get_CellState({ 2, 2 })) {
			info.isWin = true;
			info.row = -1;
			info.col = -1;
			info.isDiagonal = true;
			info.isAntiDiagonal = false;
			return info;
		}
		if (m_board.get_CellState({ 0, 2 }) != CellState::EMPTY &&
			m_board.get_CellState({ 0, 2 }) == m_board.get_CellState({ 1, 1 }) &&
			m_board.get_CellState({ 1, 1 }) == m_board.get_CellState({ 2, 0 })) {
			info.isWin = true;
			info.row = -1;
			info.col = -1;
			info.isDiagonal = false;
			info.isAntiDiagonal = true;
			return info;
		}
		return info;
	}
	uint16_t GameState::get_crossWins() const {
		return m_crossWins;
	}
	uint16_t GameState::get_circleWins() const {
		return m_cicleWins;
	}

	void GameState::add_crossWin() {
		m_crossWins++;
	}
	void GameState::add_circleWin() {
		m_cicleWins++;
	}

	void GameState::reset() {
		m_board.reset();
	}

	bool GameState::check_win_for(CellState _state) const {
		// Check rows and columns
		for (int i = 0; i < 3; ++i) {
			if ((m_board.get_CellState({ i, 0 }) == _state && m_board.get_CellState({ i, 1 }) == _state && m_board.get_CellState({ i, 2 }) == _state) ||
				(m_board.get_CellState({ 0, i }) == _state && m_board.get_CellState({ 1, i }) == _state && m_board.get_CellState({ 2, i }) == _state)) {
				return true;
			}
		}
		// Check diagonals
		if ((m_board.get_CellState({ 0, 0 }) == _state && m_board.get_CellState({ 1, 1 }) == _state && m_board.get_CellState({ 2, 2 }) == _state) ||
			(m_board.get_CellState({ 0, 2 }) == _state && m_board.get_CellState({ 1, 1 }) == _state && m_board.get_CellState({ 2, 0 }) == _state)) {
			return true;
		}
		return false;
	}

	void GameState::reset_wins() {
		m_crossWins = 0;
		m_cicleWins = 0;
	}
}