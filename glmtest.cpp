#include <Gosu/Gosu.hpp>
#include "TileSet.hpp"
#include "TileMap.hpp"
#include <cstdint>

int main();

class MyWindow : public Gosu::Window
{
  TileGL::TileSet mytilelib;
  TileGL::TileMap mytilemap;
  uint8_t tryer = 0xFF;
public:
  MyWindow()
  : Gosu::Window(640, 480) , mytilelib("settest"), mytilemap(80,40)
  {
    set_caption("GLTest");
    int i,j;
    for (i=0;i<80;i++){
      for (j=0;j<40;j++){
        if(((i+j)%2)==0){
          mytilemap.load(0xFF,i,j);
        }
        else{
          mytilemap.load(0x00,i,j);
        }
      }
    }
    mytilemap.save("maptest");
  }
  void update() override{
  }

  void draw() override{
    mytilemap.draw(0, 0, 640, 480, mytilelib);
  }
};

int main()
{
  MyWindow window;
  window.show();
  return 0;
}