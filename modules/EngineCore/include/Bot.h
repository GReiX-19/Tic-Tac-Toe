#pragma once
#include "IPlayer.h"

namespace EngineCore {
	class Bot : public IPlayer {
	public:

		Bot(PlayerMark _playerStatus);

		bool make_move(Board& _board);

		PlayerMark get_status() const override;

	};
}