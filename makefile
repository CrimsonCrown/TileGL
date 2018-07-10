OBJS = Tile.o TileCode.o TileSet.o TileMap.o
CXXFLAGS += `pkg-config --cflags gosu`
LIBS = `pkg-config --libs gosu`

mygl: $(OBJS)
	g++ gl.cpp -std=c++11 $(OBJS) $(LIBS)
testset: $(OBJS)
	g++ glstest.cpp -std=c++11 $(OBJS) $(LIBS)
testmap: $(OBJS)
	g++ glmtest.cpp -std=c++11 $(OBJS) $(LIBS)
Tile.o:
	g++ -c Tile.cpp -std=c++11
TileCode.o:
	g++ -c TileCode.cpp -std=c++11
TileSet.o:
	g++ -c TileSet.cpp -std=c++11
TileMap.o:
	g++ -c TileMap.cpp -std=c++11
clean:
	rm $(OBJS)