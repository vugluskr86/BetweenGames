#include "BattleManager.h"

BattleManager::BattleManager(uint32_t seed) :
   _seed(seed)
{
   random.seed(seed);
}

bool BattleManager::IsChance100(double chance)
{
   return std::uniform_real_distribution<double>(0, 100)(random) < chance;
}

void BattleManager::Battle(Mob& attacker, Mob& defender)
{
   //Process attacker weapons
   for(auto slot : attacker._slots) {
      Item item = slot.second;

      for(auto abil : attacker._abilities) {
         abil.first.CalcParams(abil.second);
         item = abil.first.ApplyItemParams(item);
      }

      if(item.IsWeapon() || item.IsShield()) {
              
         auto attackCount = item.GetAttackPerTurn();
         for(uint32_t attackIndex = 0; attackIndex < attackCount; attackIndex++) {

            auto power = attacker._atackPWR;

            if(item.IsWeapon()) {
               auto attackPh = item.GetDamage(DT_PHYSICAL);
               if(attackPh > 0) power *= attackPh;
            }
            if(IsChance100(attacker._crit)) {
               power *= 1.5;
            }
            else {
               if(IsChance100(defender._dodge)) {
                  continue; // Exit if dodge  TODO: GAME_LOG
               }
               else {
                  if(IsChance100(defender._absorb)) {
                     power *= 0.5;
                  }
               }
            }
    
            std::vector<Item::DamageValue> _resultDamages;
            std::vector<Item::DamageValue> itemDamages = item.GetDamages();
            for(auto damage : itemDamages) {
               auto resist = defender.GetResist(damage.first);
               auto absPower = power - (power / 100 * resist);
               auto powerMin = absPower * 0.3;
               auto powerMax = absPower * 1.2;
               absPower = std::uniform_real_distribution<double>(powerMin, powerMax)(random);
               _resultDamages.emplace_back(damage.first, absPower);
            }

            // Наносим повреждения

         }
      } 
   }
}