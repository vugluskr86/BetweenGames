#pragma once

#include "GameCommon.h"
#include "GameObject.h"
#include "TileMap.h"

#include <random>
#include <memory>

namespace BWG {
   namespace Game {

      class Mob;
      class BattleManager;
      class Player;

      class Monster : public AbstractGameObject
      {
         enum eAIState {
            AS_WALK,
            AS_IDLE
         };

         std::unique_ptr<Mob> _mob;
         std::string _name;
         eAIState _state;
         bool _attackOnTurn;
      public:
         Mob & GetMobPtr() { return *_mob; }
         std::string GetName() { return _name; }
         bool OnPlayerAttack(BattleManager& manager, Player& player);
         void Turn(BattleManager& manager, TileMapType& map);

         Monster(const std::string& baseName, Mob* mob);
      };

   }
}

