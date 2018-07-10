#include "Tile.hpp"

TileGL::Tile::Tile(){
    data = nullptr;
}

TileGL::Tile::~Tile(){
    if(data != nullptr){
    	delete data;
    }
}

bool TileGL::Tile::is_loaded() const{
	if (data == nullptr){
		return false;
	}
	else{
		return true;
	}
}

void TileGL::Tile::load(const std::string& name, int size) throw(std::invalid_argument){
    data = new Gosu::Image(name);
    if ((data->width()!= size)||(data->height() != size)){
    	delete data;
    	data = nullptr;
    	throw std::invalid_argument("image isnt tile sized (" + std::to_string(size) + "ˆ2) " + name);
    }
    else{
    	filename = "" + name;
    }
}

void TileGL::Tile::draw(double x, double y, Gosu::ZPos z) const throw(std::invalid_argument){
    if (is_loaded()){
        data->draw(x, y, z, 1, 1);
    }
    else{
    	throw std::invalid_argument("image isnt loaded, cant draw");
    }
}