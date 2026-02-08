#pragma once
#include "PlayerMark.h"
#include <cstdint>

namespace std {
	template<class T1, class T2>
	struct pair;
}

namespace EngineCore {
	class Board;

	class IPlayer {
	public:

		IPlayer(PlayerMark _playerStatus) : m_playerStatus(_playerStatus) {}

		virtual ~IPlayer() = default;

		virtual PlayerMark get_status() const = 0;

	protected:
		PlayerMark m_playerStatus;
	};
}