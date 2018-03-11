#include "Player.h"

Player::Player(eTile tile, const std::string& baseName, Mob mob) :
   TileObject()
{
   _tile = tile;
   _type = TO_PLAYER;

   _name = baseName;
   _mob = mob;
}