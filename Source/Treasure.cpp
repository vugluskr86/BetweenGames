#include "Treasure.h"

#include "TileMap.h"

Treasure::Treasure(TileMap& map) :
   _opened(false),
   _map(&map)
{ 
   _type = TO_TREASURE;

   auto layout = _map->GetLayout(TileMap::eLayouts::TL_OBJECTS);
   layout.SetCell(_pos.x, _pos.y, eTile::TT_TILES_OBJECTS_TREASURE_CLOSED);
}

void Treasure::OpenTreasure(Player& player)
{
   _opened = true;

   for(auto it : _inventory) {
      player.GetMobPtr().AddItemToInventory(it);
   }

   _inventory.clear();

   auto layout = _map->GetLayout(TileMap::eLayouts::TL_OBJECTS);
   layout.SetCell(_pos.x, _pos.y, eTile::TT_TILES_OBJECTS_TREASURE_OPEN);
}