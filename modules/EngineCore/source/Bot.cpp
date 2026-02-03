#include "Bot.h"
#include "CellState.h"
#include "Board.h"
#include <utility>

namespace EngineCore {
	Bot::Bot() : m_userStatus(Player::PLAYER_O), m_isCurrent(false) {}

	bool Bot::make_move(Board& _board) {
		CellState state = (get_status() == Player::PLAYER_X) ? CellState::X : CellState::O;



		return false;
	}
	void Bot::change_isCurrent() {
		m_isCurrent = (m_isCurrent == true) ? false : true;
	}

	Player Bot::get_status() const {
		return m_userStatus;
	}
	bool Bot::is_current() const {
		return m_isCurrent;
	}
}