#pragma once
#include <array>

namespace EngineCore {
	enum class CellState;

	class Board {
	public:

		Board();

		CellState get_CellState(std::pair<uint16_t, uint16_t> _cell) const;

		bool set_CellState(std::pair<uint16_t, uint16_t> _cell, CellState _state);

		bool is_full() const;

		void reset();

	public:
		static constexpr size_t SIZE = 3;
	private:
		std::array<std::array<CellState, SIZE>, SIZE> m_cells;
	};
}