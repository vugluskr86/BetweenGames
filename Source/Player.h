#pragma once

#include "GameCommon.h"
#include "GameObject.h"
#include "TileMap.h"

#include <memory>

namespace BWG {
   namespace Game {

      class Mob;

      class Player : public AbstractGameObject
      {
         std::unique_ptr<Mob> _mob;
         std::string _name;
         uint32_t _exp;
      public:
         Player(const std::string& baseName, std::unique_ptr<Mob> mob, double appendHp = 1.0);

         void AddExp(uint32_t exp);
         uint32_t GetExp() const { return _exp; }
         void Reset() { _exp = 0; }
        // void SetMob(const Mob& mob) { _mob = mob;  }
         Mob& GetMobPtr() { return *_mob; }
         std::string GetName() { return _name; }
      };

   }
}

