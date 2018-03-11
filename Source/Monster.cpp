#include "Monster.h"

#include "Player.h"
#include "Mob.h"
#include "BattleManager.h"

Monster::Monster(eTile tile, const std::string& baseName, Mob mob) :
   TileObject()
{
   _tile = tile;
   _type = TO_MONSTER;
   _mob = mob;

   _name = baseName;

   _mob.CalcParams(_mob._level);
}

bool Monster::OnPlayerAttack(BattleManager* manager, Player* player)
{
   Mob& playerMob = player->GetMobPtr();
   std::vector<BattleManager::BattleResult> res;
   manager->Battle(_mob, playerMob, res);
   manager->ToLog(res, _name, player->GetName());

   return playerMob.IsDie();
}


void Monster::Turn()
{
   _mob.Regen();
}