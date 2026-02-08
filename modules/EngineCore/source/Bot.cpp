#include "Bot.h"
#include "CellState.h"
#include "Board.h"
#include <utility>

namespace EngineCore {
	Bot::Bot(PlayerMark _playerStatus) : IPlayer(_playerStatus) {}

	bool Bot::make_move(Board& _board) {
		CellState state = (get_status() == PlayerMark::PLAYER_X) ? CellState::X : CellState::O;



		return false;
	}

	PlayerMark Bot::get_status() const {
		return m_playerStatus;
	}
}