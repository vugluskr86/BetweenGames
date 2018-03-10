#include "Monster.h"

Monster::Monster(eTile tile) : 
   TileObject()
{
   _tile = tile;
   _type = TO_MONSTER;
}