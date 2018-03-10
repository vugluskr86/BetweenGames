#include "Door.h"

#include "TileMap.h"

Door::Door(TileMap* map) :
   _opened(false),
   _map(map)
{
   _type = TO_DOOR;
   _tile = eTile::TT_TILES_OBJECTS_DOOR_1;

   //auto layout = _map->GetLayout(TileMap::eLayouts::TL_OBJECTS);
   //layout.SetCell(_pos.x, _pos.y, eTile::TT_TILES_OBJECTS_DOOR_1);
}

void Door::Open(Player& player)
{
   _opened = true;

   _tile = eTile::TT_TILES_OBJECTS_DOOR_2;

   auto layout = _map->GetLayout(TileMap::eLayouts::TL_STATIC);
   layout.SetCell(_pos.x, _pos.y, eTile::TT_TILES_OBJECTS_DOOR_2);
}