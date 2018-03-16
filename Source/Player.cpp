#include "GameCommon.h"
#include "Player.h"
#include "Mob.h"

namespace BWG {
   namespace Game {

      Player::Player(const std::string& baseName, Mob* mob, double appendHp) :
         AbstractGameObject(GOT_PLAYER)
      {
         _exp = 0;
         _name = baseName;

         _mob = std::make_unique<Mob>(mob);
         _mob->SetMulHp(appendHp);
         _mob->CalcParams(_mob->GetLevel());
      }

      void Player::AddExp(uint32_t exp)
      {
         _exp += exp;

         uint32_t curLevel = _exp / 8;

         if(curLevel > _mob->GetLevel()) {
            _mob->SetLevel(curLevel);
            _mob->CalcParams(_mob->GetLevel());
         }
      }
   }
}

