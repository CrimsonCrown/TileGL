#include <Gosu/Gosu.hpp>
#include "TileSet.hpp"
#include "TileMap.hpp"
#include <cstdint>

int main();

class MyWindow : public Gosu::Window
{
  TileGL::TileSet mytilelib;
  TileGL::TileMap mytilemap;
  TileGL::Tile mycursor;
  uint8_t tryer = 0xFF;
  double posx;
  double posy;
public:
  MyWindow()
  : Gosu::Window(640, 480) , mytilelib("settest"), mytilemap("maptest")
  {
    set_caption("GLTest");
    mycursor.load("cursor.png", 8);
    posx = 0;
    posy = 0;
  }
  void update() override{
    if (Gosu::Input::down(Gosu::KB_LEFT) || Gosu::Input::down(Gosu::GP_LEFT)) {
      posx-=0.015625;
    }
    if (Gosu::Input::down(Gosu::KB_RIGHT) || Gosu::Input::down(Gosu::GP_RIGHT)) {
      posx+=0.015625;
    }
    if (Gosu::Input::down(Gosu::KB_UP) || Gosu::Input::down(Gosu::GP_UP)) {
      posy-=0.015625;
    }
    if (Gosu::Input::down(Gosu::KB_DOWN) || Gosu::Input::down(Gosu::GP_DOWN)) {
      posy+=0.015625;
    }
    set_caption(std::to_string(posx) + "," + std::to_string(posy));
  }

  void draw() override{
    mytilemap.draw_tile_centered_blank(posx, posy, 640, 480, mytilelib);
    mycursor.draw(316,236,5);
  }
};

int main()
{
  MyWindow window;
  window.show();
  return 0;
}