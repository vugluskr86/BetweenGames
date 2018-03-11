#include "Monster.h"

Monster::Monster(eTile tile, const std::string& baseName, Mob mob) :
   TileObject()
{
   _tile = tile;
   _type = TO_MONSTER;
   _mob = mob;

   _name = baseName;
}