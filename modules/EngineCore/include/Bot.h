#pragma once
#include "Player.h"
#include <cstdint>

namespace std {
	template<class T1, class T2>
	struct pair;
}

namespace EngineCore {
	class Board;

	class Bot {
	public:

		Bot();

		bool make_move(Board& _board);
		void change_isCurrent();

		Player get_status() const;
		bool is_current() const;

	private:
		Player m_userStatus;
		bool m_isCurrent;
	};
}