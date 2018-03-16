#include "Monster.h"

#include "Player.h"
#include "Mob.h"
#include "BattleManager.h"

#include <vector>

namespace BWG {
   namespace Game {
   
      Monster::Monster(const std::string& baseName, Mob* mob) :
         AbstractGameObject(GOT_MONSTER)
      {
         _attackOnTurn = false;
         _state = AS_IDLE;
         _name = baseName;

         _mob = std::make_unique<Mob>(mob);
         _mob->CalcParams(_mob->GetLevel());
      }

      bool Monster::OnPlayerAttack(BattleManager& manager, Player& player)
      {
         Mob& playerMob = player.GetMobPtr();
         std::vector<BattleManager::BattleResult> res;
         manager.Battle(*_mob, playerMob, res);
         manager.ToLog(res, _name, player.GetName());
         _attackOnTurn = true;
         return playerMob.IsDie();
      }


      void Monster::Turn(BattleManager& manager, TileMapType& map)
      {
         //
         //auto mapSize = map.GetChunkSize();
         /*
         auto player = _map.GetPlayer();
         auto pPos = player->GetPos();

         // FIXME : Random
         std::mt19937 random;
         random.seed(time(0));
         std::uniform_real_distribution<> rnd01(0, 1);

         std::uniform_int_distribution<> int_rnd01(-1, 1);

         _mob.Regen();

         sf::IntRect attackRect(_pos.x - 1, _pos.y - 1, 3, 3);

         bool isAttackNeed = false;

         for(auto aX = attackRect.left; aX < attackRect.left + attackRect.width; aX++) {
            for(auto aY = attackRect.top; aY < attackRect.top + attackRect.height; aY++) {
               if(pPos.x == aX && pPos.y == aY) {
                  isAttackNeed = true;
                  break;
               }
            }
         }

         if(isAttackNeed && !_attackOnTurn) {
            Mob& playerMob = player->GetMobPtr();
            std::vector<BattleManager::BattleResult> res;
            manager->Battle(_mob, playerMob, res);
            manager->ToLog(res, _name, player->GetName());
         }
         else {
            switch(_state) {
            case AS_IDLE:
               if(rnd01(random) > 0.3) {
                  _state = AS_WALK;
               }
               break;
            case AS_WALK:
               auto x = _pos.x + int_rnd01(random);
               auto y = _pos.y + int_rnd01(random);

               if(x < 0) x = 0;
               if(y < 0) y = 0;
               //if(x >= mapSize.x) x = mapSize.x - 1;
              // if(y >= mapSize.y) y = mapSize.y - 1;

               if(_map->IsPassable(x, y)) {
                  SetPos(sf::Vector2i(x, y));
               }

               if(rnd01(random) > 0.6) {
                  _state = AS_IDLE;
               }
               break;
            }
         }

         _attackOnTurn = false;
         */
      }
   }
}

