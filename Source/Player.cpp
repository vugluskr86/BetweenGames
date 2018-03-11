#include "Player.h"

Player::Player(eTile tile, const std::string& baseName, Mob mob, double appendHp) :
   TileObject()
{
   _exp = 0;

   _tile = tile;
   _type = TO_PLAYER;

   _name = baseName;
   _mob = mob;

   _mob._mulHp = appendHp;

   _mob.CalcParams(_mob._level);
}

void Player::AddExp(uint32_t exp)
{
   _exp += exp;

   uint32_t curLevel = _exp / 8;

   if(curLevel > _mob._level) {
      _mob._level = curLevel;
      _mob.CalcParams(_mob._level);
   }
}