#pragma once
#include "IPlayer.h"

namespace EngineCore {
	class User : public IPlayer {
	public:

		User(PlayerMark _playerStatus, bool _isCurrent);

		bool make_move(Board& _board, const std::pair<uint16_t, uint16_t>& _cell);

		void change_isCurrent(bool _isCurrent) override;

		PlayerMark get_status() const override;
		bool is_current() const override;

	};
}