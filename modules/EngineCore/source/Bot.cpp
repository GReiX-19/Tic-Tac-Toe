#include "Bot.h"
#include "CellState.h"
#include "Board.h"
#include <utility>

namespace EngineCore {
	Bot::Bot(PlayerMark _playerStatus, bool _isCurrent) : IPlayer(_playerStatus, _isCurrent) {}

	bool Bot::make_move(Board& _board) {
		CellState state = (get_status() == PlayerMark::PLAYER_X) ? CellState::X : CellState::O;



		return false;
	}
	void Bot::change_isCurrent(bool _isCurrent) {
		m_isCurrent = _isCurrent;
	}

	PlayerMark Bot::get_status() const {
		return m_playerStatus;
	}
	bool Bot::is_current() const {
		return m_isCurrent;
	}
}