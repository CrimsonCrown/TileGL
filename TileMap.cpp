#include "TileMap.hpp"

//creates a tilemap from a set of sizes. Throws if one of sizes is less than 1 (empty map)
//all tiles will be set as BLANK. no offset
TileGL::TileMap::TileMap(int x, int y) throw(std::invalid_argument){
	sizex = x;
	sizey = y;
	if (x<1 || y<1){
		throw std::invalid_argument("map cannot be area-less");
	}
	map = new TileCode[sizex * sizey];
	offsetx = 0;
	offsety = 0;
	zpos = 0;
	nameval = false;
	savemark = false;
}
//creates a tilemap from a .tmf file generated through save() method
//throws if file does not exist or data is corrupt
TileGL::TileMap::TileMap(const std::string& tilemapname) throw(std::invalid_argument){
	TileCode index;
	int i,aux;
	std::ifstream SaveFile(tilemapname + ".tmf");
	nameval=true;
	filename = tilemapname;
	SaveFile>>sizex>>sizey>>zpos>>offsetx>>offsety>>savemark;
	map = new TileCode[sizex * sizey];
	i=0;
	while (SaveFile >> aux) 
	{
		index.code = (uint8_t)aux;
		map[i]=index;
		i++;
	}
	SaveFile.close();
}
//saves the tilemap before deletion if save on exit is set. deletes map data from memory
TileGL::TileMap::~TileMap(){
	if (savemark){
		save();
	}
	delete map;
}
//toggles save on exit
void TileGL::TileMap::toggle_save(){
	if (savemark){
		savemark=false;
	}
	else{
		savemark=true;
	}
}
//sets save on exit to true
void TileGL::TileMap::set_save(){
	savemark=true;
}
//sets save on exit to true, sets name of save file to parameter
void TileGL::TileMap::set_save(const std::string& name){
	savemark=true;
	filename=name;
	nameval=true;
}
//sets save on exit to false
void TileGL::TileMap::reset_save(){
	savemark=false;
}
//saves the tilemap in .tmf format, throws if no name is provided
void TileGL::TileMap::save() throw(std::invalid_argument){
	if (nameval == false){
		throw std::invalid_argument("map cannot be saved without a file name");
	}
	TileCode index;
	int i;
	std::ofstream SaveFile(filename + ".tmf");
	SaveFile<<sizex<<std::endl<<sizey<<std::endl<<zpos<<std::endl<<offsetx<<std::endl<<offsety<<std::endl<<savemark<<std::endl;
	for (i = 0;i< (sizex * sizey);i++){
		index = map[i];
		SaveFile<<(int)index.code<<std::endl;
		//SaveFile<<(int)index.code<<helper_spaces(index);
		//if (((i+1)%sizex)== 0){
		//	SaveFile<<std::endl;
		//}
	}
	SaveFile.close();
}

std::string TileGL::TileMap::helper_spaces(TileCode input){
	if (input.code >= 100){
		return (" ");
	}
	else if (input.code >= 10){
		return ("  ");
	}
	else{
		return ("   ");
	}
}
//saves the tilemap in .tmf format using specified name
void TileGL::TileMap::save(const std::string& name){
	filename=name;
	nameval=true;
	save();
}
//offsets the map on both axis
void TileGL::TileMap::offsets(int x, int y){
	offsetx = x;
	offsety = y;
}
//sets the z position of the map
void TileGL::TileMap::setz(int z){
	zpos = z;
}
//loads tile of code (first parameter) on spot (x,y) on the map, throws if spot is out of bounds
void TileGL::TileMap::load(TileCode tile, int spotx, int spoty) throw(std::invalid_argument){
	int trux = (spotx - offsetx);
	int truy = (spoty - offsety);
	if ((trux < 0)||(truy < 0)||(trux >= sizex)||(truy >= sizey)){
		throw std::invalid_argument(helper_oobexcept(spotx, spoty));
	}
	map[(spoty*sizex) + spotx] = tile;
}

std::string TileGL::TileMap::helper_oobexcept(int x, int y){
	std::string returnstatement;
	returnstatement = "position (" + std::to_string(x) + "," + std::to_string(y) + ") is out of bounds. tile must be put between (" + std::to_string(0 + offsetx) + "," + std::to_string(0 + offsety) + ") and (" + std::to_string(offsetx + sizex - 1) + "," + std::to_string(offsety + sizey - 1) + ")";
	return returnstatement;
}
//draws matrix to fill screen of size amountx,amounty from the start tile (x,y)
void TileGL::TileMap::draw(double xfarleft, double yfarup, int amountx, int amounty, const TileSet &drawset) const{
	int tsize = drawset.tile_size();
	double xin = xfarleft-offsetx;
	double yin = yfarup-offsety;
	int starttilex = floor(xin);
	int starttiley = floor(yin);
	int startpixelx = 0 - (tsize * (xin - starttilex));
	int startpixely = 0 - (tsize * (yin - starttiley));
	int endpixelx = (amountx-1);
	int endpixely = (amounty-1);
	int i,j,it,jt;
	for (({i=startpixely;it=starttiley;});i<endpixely;({i+=tsize;it++;})){
		for (({j=startpixelx;jt=starttilex;});j<endpixelx;({j+=tsize;jt++;})){
			if (((it)>=0)&&((jt)>=0)&&((it)<sizey)&&((jt)<sizex)){
				drawset.draw(map[(it*sizex) + jt], j, i, zpos);
			}
		}
	}
}

void TileGL::TileMap::draw_centered(double xcenter, double ycenter, int amountx, int amounty, const TileSet &drawset) const{
	int tsize = drawset.tile_size();
	double xin = xcenter-((amountx/2)/tsize);
	double yin = ycenter-((amounty/2)/tsize);
	draw(xin,yin,amountx,amounty,drawset);
}

void TileGL::TileMap::draw_tile_centered(double xcenter, double ycenter, int amountx, int amounty, const TileSet &drawset) const{
	int tsize = drawset.tile_size();
	double xin = (xcenter-((amountx/2)/tsize))+0.5;
	double yin = (ycenter-((amounty/2)/tsize))+0.5;
	draw(xin,yin,amountx,amounty,drawset);
}

//draws matrix to fill screen of size amountx,amounty from the start tile (x,y). BLANK will be ignored
void TileGL::TileMap::draw_blank(int xfarleft, int yfarup, int amountx, int amounty, const TileSet &drawset) const{
	int tsize = drawset.tile_size();
	double xin = xfarleft-offsetx;
	double yin = yfarup-offsety;
	int starttilex = floor(xin);
	int starttiley = floor(yin);
	int startpixelx = 0 - (tsize * (xin - starttilex));
	int startpixely = 0 - (tsize * (yin - starttiley));
	int endpixelx = (amountx-1);
	int endpixely = (amounty-1);
	int i,j,it,jt;
	for (({i=startpixely;it=starttiley;});i<endpixely;({i+=tsize;it++;})){
		for (({j=startpixelx;jt=starttilex;});j<endpixelx;({j+=tsize;jt++;})){
			if ((it>=0)&&(jt>=0)&&(it<sizey)&&(jt<sizex)&&(map[(it*sizex) + jt].code!=TileCode::BLANK.code)){
				drawset.draw(map[(it*sizex) + jt], j, i, zpos);
			}
		}
	}
}