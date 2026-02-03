#include "User.h"
#include "CellState.h"
#include "Board.h"
#include <utility>

namespace EngineCore {
	User::User() : m_userStatus(Player::PLAYER_X), m_isCurrent(true) {}

	bool User::make_move(Board _board, std::pair<uint16_t, uint16_t> _cell) {
		CellState state = (get_status() == Player::PLAYER_X) ? CellState::X : CellState::O;
		if (_board.set_CellState(_cell.first, _cell.second , state)) {
			return true;
		}
		return false;
	}
	void User::change_isCurrent() {
		m_isCurrent = (m_isCurrent == true) ? false : true;
	}

	Player User::get_status() const {
		return m_userStatus;
	}
	bool User::is_current() const {
		return m_isCurrent;
	}
}