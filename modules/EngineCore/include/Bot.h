#pragma once
#include "Board.h"
#include "CellState.h"

namespace EngineCore {
	class Bot {
	public:

		Bot(CellState _botState);

		std::pair<uint16_t, uint16_t> get_move(const Board& _board);

	private:

		bool can_win(const Board& _board, uint16_t& _outRow, uint16_t _outCol, CellState _state);
		bool find_center(const Board& _board, uint16_t& _outRow, uint16_t _outCol);
		bool find_corner(const Board& _board, uint16_t& _outRow, uint16_t _outCol);
		bool find_any(const Board& _board, uint16_t& _outRow, uint16_t _outCol);

		bool check_win(const Board& _board, CellState _state);

	private:
		CellState m_botState;
		CellState m_playerState;
	};
}