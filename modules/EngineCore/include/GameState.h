#pragma once
#include "Board.h"
#include "Player.h"

namespace EngineCore {
	class GameState {
	public:
		struct winInfo {
			bool isWin = false;
			int row = -1;
			int col = -1;
			bool isDiagonal = false;
			bool isAntiDiagonal = false;
		};
	public:
		
		GameState();

		bool make_move(int _row, int _col);
		bool is_win(Player _player) const;
		bool is_draw() const;

		const Board& get_board() const;
		const Player& get_winner() const;

		void reset();

		winInfo get_win_info() const;

	private:
		bool check_win_for(CellState _state) const;
		void determine_winner();
	private:
		Board m_board;
		Player m_current_player;
		Player m_winner;
	};
}