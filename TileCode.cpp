#include "TileCode.hpp"


TileGL::TileCode::TileCode(){
}
TileGL::TileCode::TileCode(uint8_t set){
	code = set;
}

const TileGL::TileCode TileGL::TileCode::BLANK      (0x00);