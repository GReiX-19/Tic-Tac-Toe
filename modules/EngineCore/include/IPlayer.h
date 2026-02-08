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

		IPlayer(PlayerMark _playerStatus, bool _isCurrent) : m_playerStatus(_playerStatus), m_isCurrent(_isCurrent) {}

		virtual ~IPlayer() = default;

		virtual void change_isCurrent(bool _isCurrent) = 0;

		virtual PlayerMark get_status() const = 0;
		virtual bool is_current() const = 0;

	protected:
		PlayerMark m_playerStatus;
		bool m_isCurrent;
	};
}