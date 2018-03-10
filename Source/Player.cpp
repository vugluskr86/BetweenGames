#include "Player.h"

Player::Player(eTile tile) :
   TileObject()
{
   _tile = tile;
   _type = TO_PLAYER;
}