#pragma once
#include "Board.h"
#include "User.h"
#include "Bot.h"

namespace EngineCore {
	class GameState {
	public:
		struct winInfo;
	public:
		
		GameState();

		bool make_move(const std::pair<uint16_t, uint16_t>& _cell);
		bool is_win(PlayerMark _player);
		bool is_draw();

		const Board& get_board() const;
		winInfo get_win_info() const;
		uint16_t get_crossWins() const;
		uint16_t get_circleWins() const;

		void add_crossWin();
		void add_circleWin();

		void reset();

		void reset_wins();

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
		User m_user;
		Bot m_bot;
		bool m_vsBot;
		uint16_t m_crossWins;
		uint16_t m_cicleWins;
	};
}