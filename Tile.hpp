//! \file Tile.hpp
//! Interface of the Image class and helper functions.

#pragma once

#include <Gosu/Gosu.hpp>
#include <Gosu/GraphicsBase.hpp>
#include <stdexcept>
#include <string>

namespace TileGL{
	//wrapper for Gosu::Image with a simple interface. to be used in Tilesets
	class Tile {
		Gosu::Image * data;
	public:
		std::string filename;
		//doesnt do anything, but necessary for compilation
		//(WARNING)(not problematic since tile is module interned(not visible outside of GL code unless explicitly included))
		Tile();
		//frees the image pointer if its loaded
		~Tile();
		//checks if the image is loaded, used in tileset
		bool is_loaded() const;
		//loads image of name (string name) on data
		void load(const std::string& name, int size) throw(std::invalid_argument);
		//draws the image present in image data, throws if there is none
        void draw(double x, double y, Gosu::ZPos z) const throw(std::invalid_argument);
	};
}