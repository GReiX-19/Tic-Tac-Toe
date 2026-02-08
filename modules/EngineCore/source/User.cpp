#include "User.h"
#include "CellState.h"
#include "Board.h"
#include <utility>

namespace EngineCore {
	User::User(PlayerMark _playerStatus) : IPlayer(_playerStatus) {}

	bool User::make_move(Board& _board, const std::pair<uint16_t, uint16_t>& _cell) {
		CellState state = (get_status() == PlayerMark::PLAYER_X) ? CellState::X : CellState::O;
		if (_board.set_CellState(_cell.first, _cell.second , state)) {
			return true;
		}
		return false;
	}

	PlayerMark User::get_status() const {
		return m_playerStatus;
	}
}