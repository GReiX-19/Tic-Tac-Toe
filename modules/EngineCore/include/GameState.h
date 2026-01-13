#pragma once
#include "Board.h"
#include "Player.h"

namespace EngineCore {
	class GameState {
	public:
		
		GameState();

		bool make_move(int _row, int _col);
		bool is_win(Player _player) const;
		bool is_draw() const;

		Player get_current_player() const;
		const Board& get_board() const;

		void reset();

	private:
		bool check_win_for(CellState _state) const;
	private:
		Board m_board;
		Player m_current_player;
	};
}