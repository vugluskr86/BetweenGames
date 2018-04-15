#include "TileMap.h"
#include "catch.hpp"

TEST_CASE("TileMap", "[core]")
{
   BWG::Game::TileMap<16> _map;

   BWG::Game::Tile _tile;
   _tile._decale = 2;
   _tile._ground = 4;
   _tile._solid = true;
   _tile._transparency = false;

   _map.Set(256, 245, _tile);
   auto t = _map.Get(256, 245);

   REQUIRE(t._ground == 4);
   REQUIRE(t._decale == 2);
}