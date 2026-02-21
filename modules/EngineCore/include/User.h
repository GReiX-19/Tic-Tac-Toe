#pragma once
#include "IPlayer.h"

namespace EngineCore {
	class User : public IPlayer {
	public:

		User(PlayerMark _playerStatus);

		bool make_move(Board& _board, const std::pair<uint16_t, uint16_t>& _cell, const bool& _isVsBot);

		void change_status();

		PlayerMark get_status() const override;

	};
}