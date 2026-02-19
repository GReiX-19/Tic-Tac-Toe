#include "User.h"
#include "CellState.h"
#include "Board.h"
#include <utility>

namespace EngineCore {
	User::User(PlayerMark _playerStatus) : IPlayer(_playerStatus) {}

	bool User::make_move(Board& _board, const std::pair<uint16_t, uint16_t>& _cell, const bool& _isVsBot) {
		CellState state = (get_status() == PlayerMark::PLAYER_X) ? CellState::X : CellState::O;
		if (!_isVsBot)
			if (_board.set_CellState(_cell, state))
			{
				m_playerStatus = get_status() == PlayerMark::PLAYER_X ? PlayerMark::PLAYER_O : PlayerMark::PLAYER_X;
				return true;
			}
		return false;
	}

	PlayerMark User::get_status() const {
		return m_playerStatus;
	}
}