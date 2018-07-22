//! \file TileMap.hpp
//! Interface of the TileMap class.

#pragma once

#include <Gosu/Gosu.hpp>
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
#include "TileCode.hpp"
#include "TileSet.hpp"

namespace TileGL{
	//map composed of many tiles in a matrix, described by their codes.
	class TileMap {
		TileCode * map;//the map built with codes for the tiles it is made of
		int offsetx;//translates map horizontaly by x tiles (to append to other maps)
		int offsety;//translates map verticaly by x tiles (to append to other maps)
		int zpos; //position of this map in z axis
		int sizex; //x size of map (horizontal length)
		int sizey; //y size of map (vertical length)
		std::string filename;//name of file to be saved at
		bool nameval;
		bool savemark;//marks object to be saved on deletion
		std::string helper_spaces(TileCode input);//returns amount of spaces to be in save file for spacing reasons
		std::string helper_oobexcept(int x, int y);//returns string to be exception code when map fails to load a tile

	public:
		//creates a tilemap from a set of sizes. Throws if one of sizes is less than 1 (empty map)
		//all tiles will be set as BLANK. no offset
		TileMap(int x, int y) throw(std::invalid_argument);
		//creates a tilemap from a .tmf file generated through save() method
		//throws if file does not exist or data is corrupt
		TileMap(const std::string& tilemapname) throw(std::invalid_argument);
		//saves the tilemap before deletion if save on exit is set. deletes map data from memory
		~TileMap();
		//toggles save on exit
		void toggle_save();
		//sets save on exit to true
		void set_save();
		//sets save on exit to true, sets name of save file to parameter
		void set_save(const std::string& name);
		//sets save on exit to false
		void reset_save();
		//saves the tilemap in .tmf format, throws if no name is provided
		void save() throw(std::invalid_argument);
		//saves the tilemap in .tmf format using specified name
		void save(const std::string& name);
		//offsets the map on both axis
		void offsets(int x, int y);
		//sets the z position of the map
		void setz(int z);
		//loads tile of code (first parameter) on spot (x,y) on the map, throws if spot is out of bounds
		void load(TileCode tile, int spotx, int spoty) throw(std::invalid_argument);
		//draws matrix to fill screen of size amountx,amounty from the start tile (x,y)
        void draw(double xfarleft, double yfarup, int amountx, int amounty, const TileSet &drawset) const;
        //draws map on screen centered at position (x,y)
        void draw_centered(double xcenter, double ycenter, int amountx, int amounty, const TileSet &drawset) const;
        //draws map on screen centered at tile (x,y)
        void draw_tile_centered(double xcenter, double ycenter, int amountx, int amounty, const TileSet &drawset) const;
		//draws matrix to fill screen of size amountx,amounty from the start tile (x,y). BLANK will be ignored
        void draw_blank(int startx, int starty, int amountx, int amounty, const TileSet &drawset) const;
	};
}