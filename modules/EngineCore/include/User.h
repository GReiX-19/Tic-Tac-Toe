#pragma once
#include "IPlayer.h"

namespace EngineCore {
	class User : public IPlayer {
	public:

		User(PlayerMark _playerStatus);

		bool make_move(Board& _board, const std::pair<uint16_t, uint16_t>& _cell);

		PlayerMark get_status() const override;

	};
}