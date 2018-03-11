#include "Player.h"

Player::Player(eTile tile, const std::string& baseName, Mob mob, double appendHp) :
   TileObject()
{
   _tile = tile;
   _type = TO_PLAYER;

   _name = baseName;
   _mob = mob;

   _mob._mulHp = appendHp;

   _mob.CalcParams(_mob._level);
}