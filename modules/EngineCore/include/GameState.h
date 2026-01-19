#pragma once
#include "Board.h"
#include "Player.h"

namespace EngineCore {
	class GameState {
	public:
		struct winInfo;
	public:
		
		GameState();

		bool make_move(uint16_t _row, uint16_t _col);
		bool is_win(Player _player) const;
		bool is_draw() const;

		const Board& get_board() const;
		winInfo get_win_info() const;

		void reset();

	private:

		bool check_win_for(CellState _state) const;

	public:
		struct winInfo {
			int16_t row = -1;
			int16_t col = -1;
			bool isWin = false;
			bool isDiagonal = false;
			bool isAntiDiagonal = false;
		};
	private:
		Board m_board;
		Player m_current_player;
		Player m_winner;
	};
}