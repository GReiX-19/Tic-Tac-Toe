#pragma once
#include <array>

namespace EngineCore {
	enum class CellState;

	class Board {
	public:

		Board();

		CellState get_CellState(uint16_t _row, uint16_t _col) const;

		bool set_CellState(uint16_t _row, uint16_t _col, CellState _state);

		bool is_full() const;

		void reset();

	public:
		static constexpr size_t SIZE = 3;
	private:
		std::array<std::array<CellState, SIZE>, SIZE> m_cells;
	};
}