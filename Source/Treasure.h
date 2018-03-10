#pragma once

#include "Types.h"
#include "Player.h"

class TileMap;

class Treasure : public TileObject
{
   std::vector<Item> _inventory;

   bool _opened;
   TileMap* _map;
public:
   Treasure(TileMap* map);
   void OpenTreasure(Player& player);
};