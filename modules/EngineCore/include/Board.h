#pragma once
#include <array>
#include "CellState.h"

namespace EngineCore {
	class Board {
	public:
		
		static constexpr int SIZE = 3;

	public:

		Board();

		CellState get_CellState(int row, int col) const;

		bool set_CellState(int row, int col, CellState state);

		void reset();

	private:
		std::array<std::array<CellState, SIZE>, SIZE> m_cells;
	};