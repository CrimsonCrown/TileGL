#pragma once

#include <cstdint>

namespace TileGL{
	class TileCode{//simple code to serve as key in tileset
	public:
		TileCode();
		TileCode(uint8_t set);
		std::uint8_t code;//ID for a tile, to be used in tileset
		static const TileCode BLANK;//so that blanks can be added(no need to tile everything)
	};
}