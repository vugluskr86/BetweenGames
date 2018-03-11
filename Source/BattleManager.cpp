#include "BattleManager.h"

#include "i18n.h"

BattleManager::BattleManager(std::mt19937* random) 
{
   _random = random;
}

bool BattleManager::IsChance100(double chance)
{
   return std::uniform_real_distribution<double>(0, 100)(*_random) < chance;
}

void BattleManager::Battle(Mob& attacker, Mob& defender, std::vector<BattleResult>& battleResult, bool noAnswer)
{
   //Process attacker weapons
   for(auto slot : attacker._slots) {
      Item item = slot.second;
      
      for(auto abil : attacker._abilities) {
         abil.first.CalcParams(abil.second);
         item = abil.first.ApplyItemParams(item);
      }
      
      if(item.IsWeapon() || item.IsShield()) {

         auto attackCount = attacker._attackPerTurn + item.GetAttackPerTurn();
         for(uint32_t attackIndex = 0; attackIndex < attackCount; attackIndex++) {

            BattleResult result;

            auto power = attacker._atackPWR;

            if(item.IsWeapon()) {
               auto attackPh = item.GetDamage(DT_PHYSICAL);
               if(attackPh > 0) power *= attackPh;
            }


            if(IsChance100(attacker._crit)) {
               power *= 1.5;
               result._crytical = true;
            }
            else {
               if(IsChance100(defender._dodge)) {
                  result._dodge = true;
                  continue;
               }
               else {
                  if(IsChance100(defender._absorb)) {
                     power *= 0.5;
                     result._absorbed = true;
                  }
               }
            }

            //std::vector<Item::DamageValue> _resultDamages;
            std::vector<Item::DamageValue> itemDamages = item.GetDamages();

            double allDamage = 0.0;

            for(auto damage : itemDamages) {
               auto resist = defender.GetResist(damage.first);
               auto resPower = power - (power / 100 * resist);
               auto powerMin = resPower * 0.3;
               auto powerMax = resPower * 1.2;
               resPower = std::uniform_real_distribution<double>(powerMin, powerMax)(*_random);
              // _resultDamages.emplace_back(damage.first, resPower);
               result._damages.emplace_back(damage.first, resPower, damage.first);

               allDamage += resPower;
            }
            
            result._allDamage = allDamage;

            defender._hp -= allDamage;

            if(defender._hp <= 0) {
               result._die = true;
            }
            
            battleResult.push_back(result);

            if(result._die) {
               return;
            }
         }
      } 
   }
}

/*
resDT - значение на которое подействовали резисты
asbDT - абсолютное значение

%mobname_a% hit(?:critical strike) %mobname_d% %allDamage% (resDT%type%(asbDT%type%), ...), (?:absorbed)
%mobname_d%(?:bleed,stun mobname_a) %s% for %i% turn (%bleed_damage%)
%mobname_a%(?:block chance for mobname_d) blocked %block_val%

//dodge
%mobname_d% dodged %mobname_a% hit

// die
*/

void BattleManager::ToLog(const std::vector<BattleManager::BattleResult>& res, const std::string& attakerName, const std::string& defenderName)
{
   for(auto action : res) {
      if(action._dodge) {
         GAME_LOG("%s dodged %s hit \n", defenderName.c_str(), attakerName.c_str());
         continue;
      }

      std::stringstream os;

      os << attakerName << " hit";
      if(action._crytical) {
         os << " critical strike";
      }
      os << " " << defenderName.c_str();
      os << " " << action._allDamage << " dmg";
      os << " (";

      for(auto d : action._damages) {
         os << I18n::DAMAGE_TYPES[std::get<BattleManager::eResultDamageValue::RDV_TYPE>(d)].c_str();
         os << " " << std::get<BattleManager::eResultDamageValue::RDV_VALUE>(d);
         os << "(" << std::get<BattleManager::eResultDamageValue::RD_ABS_VALUE>(d) << ")";
         os << ",";
      }

      os << ")";

      if(action._absorbed) {
         os << " ,(absorbed 50%)";
      }     

      GAME_LOG("%s \n", os.str().c_str());
   }
}