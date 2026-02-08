#pragma once
#include "IPlayer.h"

namespace EngineCore {
	class Bot : public IPlayer {
	public:

		Bot(PlayerMark _playerStatus);

		void make_move(Board& _board);

		PlayerMark get_status() const override;

	private:

		bool can_win(const Board& _board, std::pair<uint16_t, uint16_t>& _cell, const CellState& _state);
		bool find_center(const Board& _board, std::pair<uint16_t, uint16_t>& _cell);
		bool find_corner(const Board& _board, std::pair<uint16_t, uint16_t>& _cell);
		bool find_any(const Board& _board, std::pair<uint16_t, uint16_t>& _cell);

		bool check_win(const Board& _board, const CellState& _state);

	};
}