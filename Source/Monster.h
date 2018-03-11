#pragma once

#include "Types.h"
#include "Mob.h"

class BattleManager;
class TileMap;

class Monster : public TileObject
{
   enum eAIState {
    //  AS_TO_PLAYER = 0,
    //  AS_FROM_PLAYER,
      AS_WALK,
      AS_IDLE
   };

   TileMap* _map;
   Mob _mob;
   std::string _name;
   eAIState _state;
   bool _attackOnTurn;
public:
   Mob & GetMobPtr()
   { return _mob; }
   std::string GetName() { return _name; }
   bool OnPlayerAttack(BattleManager* manager, Player* player);
   void Turn(BattleManager* manager);

   Monster(eTile tile, const std::string& baseName, Mob mob, TileMap* map);
};