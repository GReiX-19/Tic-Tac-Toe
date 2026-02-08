#pragma once
#include "IPlayer.h"

namespace EngineCore {
	class Bot : public IPlayer {
	public:

		Bot(PlayerMark _playerStatus, bool _isCurrent);

		bool make_move(Board& _board);

		void change_isCurrent(bool _isCurrent) override;

		PlayerMark get_status() const override;
		bool is_current() const override;

	};
}