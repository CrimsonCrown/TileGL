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
  int posx;
  int posy;
public:
  MyWindow()
  : Gosu::Window(640, 480) , mytilelib("settest"), mytilemap("maptest")
  {
    set_caption("GLTest");
    posx = 0;
    posy = 0;
  }
  void update() override{
    if (Gosu::Input::down(Gosu::KB_LEFT) || Gosu::Input::down(Gosu::GP_LEFT)) {
      posx-=1;
    }
    if (Gosu::Input::down(Gosu::KB_RIGHT) || Gosu::Input::down(Gosu::GP_RIGHT)) {
      posx+=1;
    }
    if (Gosu::Input::down(Gosu::KB_UP) || Gosu::Input::down(Gosu::GP_UP)) {
      posy-=1;
    }
    if (Gosu::Input::down(Gosu::KB_DOWN) || Gosu::Input::down(Gosu::GP_DOWN)) {
      posy+=1;
    }
  }

  void draw() override{
    mytilemap.draw(posx, posy, 640, 480, mytilelib);
  }
};

int main()
{
  MyWindow window;
  window.show();
  return 0;
}