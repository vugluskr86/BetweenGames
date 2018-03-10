#pragma once

#include "Types.h"

class TileMap;

class Door : public TileObject
{
   bool _opened;
   TileMap* _map;
public:
   Door(TileMap* map);
   void Open(Player& player);
   bool IsOpen() const { return _opened;  }
};