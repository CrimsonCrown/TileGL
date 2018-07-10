#include "TileSet.hpp"


//creates a tileset from a default tile for not found images or undefined codes
TileGL::TileSet::TileSet(const std::string& defaultname, int size) throw(std::invalid_argument){
	tilesize=size;
	savemark=false;
	nameval=false;
	invalid_default.load(defaultname,tilesize);
}
//creates a tileset from a .tsf file generated through save() method
//throws if file does not exist or data is corrupt
TileGL::TileSet::TileSet(const std::string& tilesetname) throw(std::invalid_argument){
	TileCode index;
	int i;
	char charaux;
	std::string nameaux;
	std::ifstream SaveFile(tilesetname + ".tsf");
	nameval=true;
	filename = tilesetname;
	SaveFile>>tilesize>>nameaux>>savemark;
	invalid_default.load(nameaux,tilesize);
	while (SaveFile >> i) 
	{
		SaveFile>>charaux>>nameaux;
		index.code = (uint8_t) i;
		load(nameaux,index);
	}
	SaveFile.close();
}
//saves the tileset before deletion if savemark is set
TileGL::TileSet::~TileSet(){
	if (savemark){
		save();
	}
}
//toggles savemark
void TileGL::TileSet::toggle_save(){
	if (savemark){
		savemark=false;
	}
	else{
		savemark=true;
	}
}
//sets savemark to true
void TileGL::TileSet::set_save(){
	savemark=true;
}
//sets savemark to true, sets name of save file to name
void TileGL::TileSet::set_save(const std::string& name){
	savemark=true;
	filename=name;
	nameval=true;
}
//sets savemark to false
void TileGL::TileSet::reset_save(){
	savemark=false;
}
//saves the tileset in .tsf format, throws if no name is provided
void TileGL::TileSet::save() throw(std::invalid_argument){
	if (nameval == false){
		throw std::invalid_argument("set cannot be saved without a file name");
	}
	TileCode index;
	int i;
	std::ofstream SaveFile(filename + ".tsf");
	SaveFile<<tilesize<<std::endl<<invalid_default.filename<<std::endl<<savemark<<std::endl;
	for (i = 0x00;i<=0xFF;i++){
		index.code = (uint8_t)i;
		if (tiles[index.code].is_loaded()){
			SaveFile<<(int)index.code<<":"<<tiles[index.code].filename<<std::endl;
		}
	}
	SaveFile.close();
}
//saves the tileset in .tsf format using specified name
void TileGL::TileSet::save(const std::string& name){
	filename=name;
	nameval=true;
	save();
}
//loads image of name (string name) on Tile on set[code], throws if cant load image or spot is already taken
void TileGL::TileSet::load(const std::string& name, TileCode code) throw(std::invalid_argument){
	if(tiles[code.code].is_loaded()){
		throw std::invalid_argument("Tile " + std::to_string(code.code) + "is taken by " + tiles[code.code].filename);
	}
	load_overwrite(name,code);
}
//loads image of name (string name) on Tile on set[code], throws if cant load image
void TileGL::TileSet::load_overwrite(const std::string& name, TileCode code) throw(std::invalid_argument){
	try{
		tiles[code.code].load(name,tilesize);
	}
	catch(const std::invalid_argument &exp){
		throw std::invalid_argument("image " + name + "could not be loaded");
	}
}
//draws tile with upper left corner on position (x,y) layered at z
//if the tile is not defined, draws default tile instead
void TileGL::TileSet::draw(TileCode code, double x, double y, double z) const{
	if(tiles[code.code].is_loaded()){
		tiles[code.code].draw(x,y,z);
	}
	else{
		invalid_default.draw(x,y,z);
	}
}

int TileGL::TileSet::tile_size() const{
	return tilesize;
}