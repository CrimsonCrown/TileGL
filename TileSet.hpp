//! \file TileSet.hpp
//! Interface of the TileSet class.

#pragma once

#include <Gosu/Gosu.hpp>
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
#include "Tile.hpp"
#include "TileCode.hpp"

namespace TileGL{
	//set of tiles to be used when rendering a map.
	class TileSet {
		Tile tiles[256];//the tile set
		Tile invalid_default;//default tile for invalid codes
		std::string filename;//name of file to be saved at
		bool nameval;
		int tilesize;//all tiles in a set must be compatible with each other
		bool savemark;//marks object to be saved on deletion

	public:
		//creates a tileset from a default tile for not found images or undefined codes
		TileSet(const std::string& defaultname, int size) throw(std::invalid_argument);
		//creates a tileset from a .tsf file generated through save() method
		//throws if file does not exist or data is corrupt
		TileSet(const std::string& tilesetname) throw(std::invalid_argument);
		//saves the tileset before deletion if save on exit is set
		~TileSet();
		//toggles save on exit
		void toggle_save();
		//sets save on exit to true
		void set_save();
		//sets save on exit to true, sets name of save file to parameter
		void set_save(const std::string& name);
		//sets save on exit to false
		void reset_save();
		//saves the tileset in .tsf format, throws if no name is provided
		void save() throw(std::invalid_argument);
		//saves the tileset in .tsf format using specified name
		void save(const std::string& name);
		//loads image of name (first parameter) on Tile on set indexed at (second parameter), throws if cant load image or spot is already taken
		void load(const std::string& name, TileCode code) throw(std::invalid_argument);
		//loads image of name (first parameter) on Tile on set indexed at (second parameter), throws if cant load image
		void load_overwrite(const std::string& name, TileCode code) throw(std::invalid_argument);
		//draws tile with upper left corner on position (x,y) layered at z
		//if the tile is not defined, draws default tile instead
        void draw(TileCode code, double x, double y, double z) const;
        //returns size of tiles. simple getter
        int tile_size() const;
	};
}